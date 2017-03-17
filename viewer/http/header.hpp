//
// http_header.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _http_header_hpp_INCLUDED_
#define _http_header_hpp_INCLUDED_

#include <string>
#include <map>


namespace http {


	/// \brief HTTP-Header
	typedef std::multimap< std::string, std::string > header;


}

#endif
