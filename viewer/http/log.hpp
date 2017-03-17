#ifndef _http_log_hpp_INCLUDED_
#define _http_log_hpp_INCLUDED_

#include <tools/size_io.hpp>
#include <tools/point_io.hpp>
#include <tools/std_array_io.hpp>
#include <tools/std_vector_io.hpp>

#include <tools/timed_log.hpp>

#include <fstream>
#include <iostream>


namespace http{


	namespace config{ namespace log{


		inline std::ostream& stream(){ return std::clog; }


	} }


	namespace log{


		template < typename Log >
		struct base_log: tools::timed_log< Log >{
			static void output(std::string const& str){
				config::log::stream() << str << std::flush;
			}
		};

		struct server: base_log< server >{
			static bool is_active(){
				return false;
			}

			void prefix(std::ostringstream& os)const{
				base_log< server >::prefix(os);
				os << "HttpServer: ";
			}
		};


	}

}


#endif
