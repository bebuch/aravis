//
// http_request.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _http_request_hpp_INCLUDED_
#define _http_request_hpp_INCLUDED_

#include "header.hpp"

#include <string>
#include <vector>


namespace http {


	/// \brief A request received from a client.
	struct request{
		std::string method;
		std::string uri;
		int http_version_major;
		int http_version_minor;
		header headers;
	};


}

#endif
