//
// http_server_request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _http_server_request_handler_hpp_INCLUDED_
#define _http_server_request_handler_hpp_INCLUDED_

#include <boost/noncopyable.hpp>

#include <string>
#include <memory>

namespace http {
	struct reply;
	struct request;
}

namespace http { namespace server {


	class connection;

	typedef std::shared_ptr< connection > connection_ptr;

	/// \brief The common handler for all incoming requests.
	class request_handler: private boost::noncopyable{
	public:
		/// \brief Virtual Standard-Destructor
		virtual ~request_handler(){}

		/// \brief Handle a request and produce a reply.
		virtual bool handle_request(connection_ptr const& connection, http::request const& req, http::reply& rep) = 0;

		/// \brief Is called by server shutdown
		virtual void shutdown(){}
	};


} }

#endif
