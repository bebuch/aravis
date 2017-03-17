/// \file tools/timed_log.hpp
/// \author Benjamin Buch (benni.buch@gmail.com)
/// \brief A log that measures the time of its content
///
/// Copyright (c) 2013-2015 Benjamin Buch (benni dot buch at gmail dot com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///
#ifndef _tools_timed_log_hpp_INCLUDED_
#define _tools_timed_log_hpp_INCLUDED_

#include "log.hpp"
#include "time_output.hpp"


namespace tools{


	struct timed_log_base{
		timed_log_base(): start(std::chrono::system_clock::now()){}

		void extended_prefix(bool has_body, std::ostringstream& os)const{
			auto end = std::chrono::system_clock::now();

			time_output(os, start);

			if(has_body){
				os << " ( " << std::setfill(' ') << std::setprecision(3) << std::setw(12) << std::chrono::duration< double, std::milli >(end - start).count() << "ms ) ";
			}else{
				os << " ( no content     ) ";
			}
		}

		std::chrono::system_clock::time_point start;
	};

	template < typename Log >
	struct timed_log: timed_log_base, log_base< Log >{
		void prefix(std::ostringstream& os)const{
			extended_prefix(log_base< Log >::has_body, os);
		}
	};


}

#endif