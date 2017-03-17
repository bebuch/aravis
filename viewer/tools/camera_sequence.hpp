/// \file tools/camera_sequence.hpp
/// \author Benjamin Buch (benni.buch@gmail.com)
/// \brief Vector of vector of bitmaps
///
/// Copyright (c) 2014-2015 Benjamin Buch (benni dot buch at gmail dot com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///
#ifndef _tools_camera_sequence_hpp_INCLUDED_
#define _tools_camera_sequence_hpp_INCLUDED_

#include "sequence.hpp"


namespace tools {


	/// \brief List of tools::sequence< T >
	template < typename T >
	using camera_sequence = std::vector< sequence< T > >;


}

#endif
