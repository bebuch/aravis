//
// http_mime_types.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _http_mime_types_hpp_INCLUDED_
#define _http_mime_types_hpp_INCLUDED_

#include <string>
#include <map>


namespace http {

	namespace config { namespace mime_types {


			std::map< std::string, std::string > init_extension_to_type_mapper();


	} }

	namespace mime_types {

		/// \brief Convert a file extension into a MIME type.
		std::string extension_to_type(std::string const& extension);

	}

}

#endif
