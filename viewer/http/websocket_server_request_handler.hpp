//
// http_websocket_server_request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _http_websocket_server_request_handler_hpp_INCLUDED_
#define _http_websocket_server_request_handler_hpp_INCLUDED_

#include "server_request_handler.hpp"

#include <map>


namespace http { namespace websocket { namespace server {


	class service;

	using service_ptr = std::shared_ptr< service >;

	/// \brief Handles Websocket-requests
	class request_handler: public http::server::request_handler{
	public:
		/// \brief Handle a request and produce a reply.
		virtual bool handle_request(http::server::connection_ptr const& connection, http::request const& req, http::reply& rep) override;

		/// \brief Call shutdown() for all services
		virtual void shutdown() override;

		/// \brief Binds a name to websocket service.
		bool register_service(std::string const& name, service_ptr const& service);

	private:
		/// \brief The websocket services
		std::map< std::string, service_ptr > services_;
	};


} } }

#endif
