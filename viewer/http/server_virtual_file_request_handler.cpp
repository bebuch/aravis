//
// http_server_virtual_file_request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server_virtual_file_request_handler.hpp"

#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"


namespace http { namespace server {


	virtual_file_request_handler::virtual_file_request_handler(std::string const& dir):
		dir_(dir)
		{}

	bool virtual_file_request_handler::handle_request(connection_ptr const& connection, http::request const& req, http::reply& rep){
		// Request path must be absolute and not contain "/..".
		if(!check_uri(req, rep)) return false;

		// Check if requestet file in virtual subdirectory
		std::string filename = dir_.empty() ? req.uri : req.uri.substr(1);
		std::size_t dir_length = dir_.size() + 1;
		if(dir_length > filename.size() || filename.compare(0, dir_length, dir_ + "/") != 0){
			rep = http::reply::stock_reply(http::reply::bad_request);
			return false;
		}

		// Erase subdirectory from filename
		filename = filename.substr(dir_length);

		// Check if file exists
		auto file = files_.find(filename);
		if(file == files_.end()){
			rep = http::reply::stock_reply(http::reply::not_found);
			return false;
		}

		/// Set content length and mime type
		rep.status = reply::ok;
		rep.content = std::get< 1 >(file->second);
		set_http_header(req, rep, mime_types::extension_to_type(std::get< 0 >(file->second)));

		return true;
	}

	/// Add a new virtual file
	bool virtual_file_request_handler::add(std::string const& filename, std::string const& mime_type, std::string const& content){
		if(files_.find(filename) != files_.end()) return false;

		files_.insert(make_pair(filename, make_pair(mime_type, content)));
		return true;
	}

	/// erase a file
	bool virtual_file_request_handler::erase(std::string const& filename){
		return files_.erase(filename) > 0;
	}

	/// erase all files
	void virtual_file_request_handler::clear(){
		files_.clear();
	}


} }
