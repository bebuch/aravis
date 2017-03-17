/// \file tools/sequence.hpp
/// \author Benjamin Buch (benni.buch@gmail.com)
/// \brief Vector of bitmaps
///
/// Copyright (c) 2014-2015 Benjamin Buch (benni dot buch at gmail dot com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///
#ifndef _tools_sequence_hpp_INCLUDED_
#define _tools_sequence_hpp_INCLUDED_

#include "bitmap.hpp"

#include <vector>


namespace tools {


	/// \brief List of tools::bitmap< T >
	template < typename T >
	using sequence = std::vector< bitmap< T > >;


}

#endif
