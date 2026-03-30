/**
 * @file		kyra-websocket-server.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_WEBSOCKET_SERVER_H_
#define _HEADER_KYRA_WEBSOCKET_SERVER_H_

/* Include */

#include <thread>
#include <mutex>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

#include "kyra-websocket-session.h"
#include "kyra-exception.h"
#include "kyra-logger.h"

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

/* defines typedef & constant */

/* MACRO functions */

/* Inline define */

/* Attributes */
/*
[[noreturn]]
[[deprecated]]
[[fallthrough]]
[[nodiscard]]
[[maybe_unused]]
*/

/* Declaration */

/* ASM codes */
// extern "C" int func(int x, int y);

/* Data structures declaration - struct & class */

namespace kyra {
	namespace asio = boost::asio;
	namespace ssl = asio::ssl;
//	namespace beast = boost::beast;
//	namespace http = beast::http;
//	namespace websocket = beast::websocket;

	using tcp = asio::ip::tcp;
	
	class WebSocketServer {
	public:
		explicit WebSocketServer(const std::string& port);
		
		virtual ~WebSocketServer(void) noexcept = default;

		void run(void);
		
	private:
		void thread_function(tcp::socket socket);

		std::string port;
		
		asio::io_context ioc;
		
		ssl::context ctx;
		
		tcp::acceptor acceptor;
	};
}

/* Functions declaration */

// void swap(Sample&, Sample&) noexcept;

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
