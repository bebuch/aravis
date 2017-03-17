/* Aravis - Digital camera library
 *
 * Copyright © 2009-2012 Emmanuel Pacaud
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Author: Emmanuel Pacaud <emmanuel@gnome.org>
 */

#include <arvconfig.h>
#include <arvviewer.h>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <arv.h>
#include <stdlib.h>
#include <libnotify/notify.h>
#include <libintl.h>
#include <http/server_server.hpp>
#include <http/server_file_request_handler.hpp>
#include <http/server_lambda_request_handler.hpp>
#include <http/websocket_server_request_handler.hpp>
#include <http/websocket_server_service.hpp>
#include <fstream>
#include <sstream>
#include <iostream>


namespace aravis_viewer{


	struct service: http::websocket::server::service{};

	class request_handler: public http::server::lambda_request_handler{
	public:
		request_handler();

		std::shared_ptr< aravis_viewer::service > service(){
			return websocket_service_;
		}

	private:
		/// \brief The WebSocket-Service
		std::shared_ptr< aravis_viewer::service > websocket_service_;

		/// \brief Handler for Websocket-Requests
		http::websocket::server::request_handler websocket_handler_;

		/// \brief Handler for normal HTTP-File-Requests
		http::server::file_request_handler http_file_handler_;
	};


	request_handler::request_handler() :
		http::server::lambda_request_handler(
			[this](
				http::server::connection_ptr connection,
				http::request const& req,
				http::reply& rep
			){
				return
					websocket_handler_.handle_request(connection, req, rep) ||
					http_file_handler_.handle_request(connection, req, rep);
			},
			[this]{
				websocket_handler_.shutdown();
			}
		),
		websocket_service_(std::make_shared< aravis_viewer::service >()),
		http_file_handler_(".")
	{
		websocket_handler_.register_service("scheduler", websocket_service_);
	}


}

G_BEGIN_DECLS

static char *arv_viewer_option_debug_domains = NULL;
static gboolean arv_viewer_option_auto_socket_buffer = FALSE;
static gboolean arv_viewer_option_no_packet_resend = FALSE;
static unsigned int arv_viewer_option_packet_timeout = 20;
static unsigned int arv_viewer_option_frame_retention = 100;

G_END_DECLS


std::shared_ptr< aravis_viewer::service > sender;

std::size_t frame_devide_count = 0;
std::ostringstream png_os(std::ios::out | std::ios::binary);

void output_png(png_structp png_ptr, png_bytep buffer, png_size_t size){
	png_os.write(reinterpret_cast< char const* >(buffer), size);
}

void flush_png(char const* filename){
	auto str = png_os.str();
	png_os.str("");
	png_os.clear();

	if(sender && frame_devide_count++ == 5){
		frame_devide_count = 0;
		sender->send_binary(str);
	}

	if(filename){
		std::ofstream os(filename, std::ios::out | std::ios::binary);
		os.write(str.data(), str.size());
	}
}


static const GOptionEntry arv_viewer_option_entries[] =
{
	{
		"auto-buffer-size",			'a', 0, G_OPTION_ARG_NONE,
		&arv_viewer_option_auto_socket_buffer,	"Auto socket buffer size", NULL
	},
	{
		"no-packet-resend",			'r', 0, G_OPTION_ARG_NONE,
		&arv_viewer_option_no_packet_resend,	"No packet resend", NULL
	},
	{
		"packet-timeout", 			'p', 0, G_OPTION_ARG_INT,
		&arv_viewer_option_packet_timeout, 	"Packet timeout (ms)", NULL
	},
	{
		"frame-retention", 			'm', 0, G_OPTION_ARG_INT,
		&arv_viewer_option_frame_retention, 	"Frame retention (ms)", NULL
	},
	{
		"debug", 				'd', 0, G_OPTION_ARG_STRING,
		&arv_viewer_option_debug_domains, 	"Debug domains", NULL
	},
	{ NULL }
};

int
main (int argc, char **argv)
{
	auto handler = std::make_unique< aravis_viewer::request_handler >();
	sender = handler->service();

	http::server::server server("8090", std::move(handler), 1);


	ArvViewer *viewer;
	int status;
	GOptionContext *context;
	GError *error = NULL;

	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	arv_g_thread_init (NULL);

	gtk_init (&argc, &argv);
	gst_init (&argc, &argv);

	context = g_option_context_new (NULL);
	g_option_context_add_main_entries (context, arv_viewer_option_entries, NULL);
	g_option_context_add_group (context, gtk_get_option_group (TRUE));
	g_option_context_add_group (context, gst_init_get_option_group ());
	if (!g_option_context_parse (context, &argc, &argv, &error)) {
		g_option_context_free (context);
		g_print ("Option parsing failed: %s\n", error->message);
		g_error_free (error);
		return EXIT_FAILURE;
	}

	g_option_context_free (context);

	arv_debug_enable (arv_viewer_option_debug_domains);

	viewer = arv_viewer_new ();
	if (!ARV_IS_VIEWER (viewer))
		return EXIT_FAILURE;

	arv_viewer_set_options (viewer,
				arv_viewer_option_auto_socket_buffer,
				!arv_viewer_option_no_packet_resend,
				arv_viewer_option_packet_timeout,
				arv_viewer_option_frame_retention);

	notify_init ("Aravis Viewer");

	status = g_application_run (G_APPLICATION (viewer), argc, argv);

	g_object_unref (viewer);

	notify_uninit ();

	return status;
}
