//
// http_server_server.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _http_server_server_hpp_INCLUDED_
#define _http_server_server_hpp_INCLUDED_

#include "server_connection.hpp"
#include "server_request_handler.hpp"

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#include <string>
#include <vector>
#include <future>
#include <mutex>


namespace http { namespace server {


	/// \brief The top-level class of the HTTP server.
	class server: private boost::noncopyable{
	public:
		/// \brief Construct the server to listen on the specified TCP port.
		server(
			std::string const& port,
			std::unique_ptr< request_handler >&& handler,
			std::size_t thread_pool_size
		);

		/// \brief Tell all handlers, that the server shutdowns
		~server();

	private:
		/// \brief Run the server's io_service loop.
		void run(std::size_t thread_pool_size);

		/// \brief Initiate an asynchronous accept operation.
		void start_accept();

		/// \brief Stop asynchronous accept operation.
		void stop_accept();

		/// \brief Handle completion of an asynchronous accept operation.
		void handle_accept(connection_ptr const& new_connection, boost::system::error_code const& err);

		/// \brief The handler for all incoming requests.
		std::unique_ptr< request_handler > request_handler_;

		/// \brief The io_service used to perform asynchronous operations.
		boost::asio::io_service io_service_;

		/// \brief Acceptor used to listen for incoming connections.
		boost::asio::ip::tcp::acceptor acceptor_;

		/// \brief Thread synchronization.
		std::mutex acceptor_mutex_;

		/// \brief The working threads.
		std::vector< std::future< void > > futures_;
	};


} }

#endif
