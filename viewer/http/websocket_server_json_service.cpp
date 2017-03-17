//
// http_websocket_server_json_service.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "websocket_server_json_service.hpp"

#include <sstream>

namespace http { namespace websocket { namespace server {


	std::string to_json(boost::property_tree::ptree const& data){
		std::ostringstream message;
		write_json(message, data);
		return message.str();
	}

	void json_service::json_callback_type::operator()(std::string const& message, http::server::connection_ptr const& connection)const{
		if (!json_callback_) return;

		boost::property_tree::ptree data;
		std::istringstream is(message);
		read_json(is, data);
		json_callback_(data, connection);
	}

	void json_service::send_json(boost::property_tree::ptree const& data){
		send_utf8(to_json(data));
	}

	void json_service::send_json(boost::property_tree::ptree const& data, http::server::connection_ptr const& connection){
		send_utf8(to_json(data), connection);
	}


} } }
