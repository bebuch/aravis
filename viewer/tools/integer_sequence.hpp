/// \file tools/integer_sequence.hpp
/// \author Benjamin Buch (benni.buch@gmail.com)
/// \brief An implementation of std::integer_sequence for MS VC 2013 …
///
/// Copyright (c) 2013-2015 Benjamin Buch (benni dot buch at gmail dot com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///
#ifndef _tools_integer_sequence_hpp_INCLUDED_
#define _tools_integer_sequence_hpp_INCLUDED_

#include <cstddef>
#include <cstdint>


namespace tools{


	template < typename T, T ... I > struct integer_sequence{
		using type = integer_sequence;
		static std::size_t size(){ return sizeof...(I); }
	};

	template < typename T, typename S1, typename S2 >
	struct concat;

	template < typename T, T ... I1, T ... I2 >
	struct concat< T, integer_sequence< T, I1 ... >, integer_sequence< T, I2 ... > >:
		integer_sequence< T, I1 ..., T(sizeof...(I1)+I2) ... >{};

	template < typename T, T N >
	struct make_integer_sequence_impl:
		concat< T, typename make_integer_sequence_impl< T, T(N / T(2)) >::type, typename make_integer_sequence_impl< T, T(N - N / T(2)) >::type >::type {};


	template <> struct make_integer_sequence_impl< std::uint8_t, std::uint8_t(0) >: integer_sequence< std::uint8_t >{};
	template <> struct make_integer_sequence_impl< std::uint8_t, std::uint8_t(1) >: integer_sequence< std::uint8_t, std::uint8_t(0) >{};

	template <> struct make_integer_sequence_impl< std::int8_t, std::int8_t(0) >: integer_sequence< std::int8_t >{};
	template <> struct make_integer_sequence_impl< std::int8_t, std::int8_t(1) >: integer_sequence< std::int8_t, std::int8_t(0) >{};


	template <> struct make_integer_sequence_impl< char, char(0) >: integer_sequence< char >{};
	template <> struct make_integer_sequence_impl< char, char(1) >: integer_sequence< char, char(0) >{};

	template <> struct make_integer_sequence_impl< bool, false >: integer_sequence< bool >{};
	template <> struct make_integer_sequence_impl< bool, true >: integer_sequence< bool, false >{};


	template <> struct make_integer_sequence_impl< std::uint16_t, std::uint16_t(0) >: integer_sequence< std::uint16_t >{};
	template <> struct make_integer_sequence_impl< std::uint16_t, std::uint16_t(1) >: integer_sequence< std::uint16_t, std::uint16_t(0) >{};

	template <> struct make_integer_sequence_impl< std::int16_t, std::int16_t(0) >: integer_sequence< std::int16_t >{};
	template <> struct make_integer_sequence_impl< std::int16_t, std::int16_t(1) >: integer_sequence< std::int16_t, std::int16_t(0) >{};


	template <> struct make_integer_sequence_impl< std::uint32_t, std::uint32_t(0) >: integer_sequence< std::uint32_t >{};
	template <> struct make_integer_sequence_impl< std::uint32_t, std::uint32_t(1) >: integer_sequence< std::uint32_t, std::uint32_t(0) >{};

	template <> struct make_integer_sequence_impl< std::int32_t, std::int32_t(0) >: integer_sequence< std::int32_t >{};
	template <> struct make_integer_sequence_impl< std::int32_t, std::int32_t(1) >: integer_sequence< std::int32_t, std::int32_t(0) >{};


	template <> struct make_integer_sequence_impl< std::uint64_t, std::uint64_t(0) >: integer_sequence< std::uint64_t >{};
	template <> struct make_integer_sequence_impl< std::uint64_t, std::uint64_t(1) >: integer_sequence< std::uint64_t, std::uint64_t(0) >{};

	template <> struct make_integer_sequence_impl< std::int64_t, std::int64_t(0) >: integer_sequence< std::int64_t >{};
	template <> struct make_integer_sequence_impl< std::int64_t, std::int64_t(1) >: integer_sequence< std::int64_t, std::int64_t(0) >{};


	template < typename T, T N >
	using make_integer_sequence = typename make_integer_sequence_impl< T, N >::type;

	template < std::size_t ... I >
	using index_sequence = integer_sequence< std::size_t, I ... >;

	template < std::size_t N >
	using make_index_sequence = typename make_integer_sequence_impl< std::size_t, N >::type;


}


#endif
