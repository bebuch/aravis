/// \file tools/timed_hierarchic_log.hpp
/// \author Benjamin Buch (benni.buch@gmail.com)
/// \brief A log that combines the timed and the hierachic log
///
/// Copyright (c) 2014-2015 Benjamin Buch (benni dot buch at gmail dot com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///
#ifndef _tools_timed_hierarchic_log_hpp_INCLUDED_
#define _tools_timed_hierarchic_log_hpp_INCLUDED_

#include "timed_log.hpp"
#include "hierarchic_log.hpp"


namespace tools{


	template < typename Log >
	struct timed_hierarchic_log: timed_log_base, hierarchic_log_base, log_base< Log > {
		using hierarchic_log_base::first;

		void prefix(std::ostringstream& os)const{
			timed_log_base::extended_prefix(log_base< Log >::has_body, os);
			hierarchic_log_base::prefix(os);
		}
	};


}


#endif
