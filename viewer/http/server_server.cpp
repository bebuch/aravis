//
// http_server_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2012 Benjamin Buch (benni dot buch at googlemail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server_server.hpp"
#include "log.hpp"

#include <tools/exception_catcher.hpp>

#include <thread>
#include <memory>
#include <vector>


namespace http { namespace server {


	server::server(
		std::string const& port,
		std::unique_ptr< request_handler >&& handler,
		std::size_t thread_pool_size
	):
		request_handler_(std::move(handler)),
		acceptor_(io_service_)
	{
		// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
		boost::asio::ip::tcp::resolver resolver(io_service_);
		boost::asio::ip::tcp::resolver::query query(port);
		boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));

		try{
			acceptor_.bind(endpoint);
		}catch(std::runtime_error const& error){
			throw std::runtime_error("Binding server to endpoint failed (Port: " + port + "); " + error.what());
		}

		acceptor_.listen();

		start_accept();

		run(thread_pool_size);
	}

	server::~server()try{
		// Do not accept new connections
		stop_accept();

		// Tell the handler that the server shutdowns
		request_handler_->shutdown();

		for(auto& future: futures_){
			if(future.valid()) future.wait();
		}
	}catch(std::exception const& e){
		std::cerr << "http::server::server deconstructed with exception: " << e.what() << std::endl;
	}catch(...){
		std::cerr << "http::server::server deconstructed with unknown exception" << std::endl;
	}

	void server::run(std::size_t thread_pool_size){
		// Create a pool of threads to run all of the io_services.
		futures_.reserve(thread_pool_size);
		for(std::size_t i = 0; i < thread_pool_size; ++i){
			futures_.emplace_back(std::async(std::launch::async, [this]{
				while(!tools::exception_catcher([](log::server& os){ os << "I/O-Service"; }, [this]{
					io_service_.run();
				}));
			}));
		}
	}

	void server::start_accept(){
		std::lock_guard< std::mutex > lock(acceptor_mutex_);

		if(!acceptor_.is_open()) return;

		auto new_connection = make_shared_connection(io_service_);

		acceptor_.async_accept(
			new_connection->socket(),
			[this, new_connection](boost::system::error_code const& err){
				handle_accept(new_connection, err);
			}
		);
	}

	void server::stop_accept(){
		std::lock_guard< std::mutex > lock(acceptor_mutex_);

		acceptor_.close();
	}

	void server::handle_accept(connection_ptr const& new_connection, boost::system::error_code const& err){
		if(!err){
			new_connection->start(*request_handler_);
		}

		start_accept();
	}


} }
