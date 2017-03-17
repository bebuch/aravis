//
// http_websocket_frame.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012-2013 Benjamin Buch (benni dot buch at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _http_websocket_frame_hpp_INCLUDED_
#define _http_websocket_frame_hpp_INCLUDED_

#include <string>


namespace http { namespace websocket {

	/// \brief A WebSocket frame
	struct frame{
		/// \brief final frame?
		bool fin;

		/// \brief Which kind of frame is it?
		enum opcode{
			continuation_frame = 0x0,
			text_frame = 0x1,
			binary_frame = 0x2,
			connection_close = 0x8,
			ping = 0x9,
			pong = 0xA
		} code;

		/// \brief Data of the frame
		std::string data;
	};


} }

#endif
