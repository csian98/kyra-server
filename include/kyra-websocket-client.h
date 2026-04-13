/**
 * @file		kyra-websocket-client.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_WEBSOCKET_CLIENT_H_
#define _HEADER_KYRA_WEBSOCKET_CLIENT_H_

/* Include */

#include <thread>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

#include <nlohmann/json.hpp>

#include "kyra-protocol.h"
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
	namespace beast = boost::beast;
	namespace http = beast::http;
	namespace websocket = beast::websocket;
 
	using tcp = asio::ip::tcp;
	using json = nlohmann::json;
	
	class WebSocketClient {
	public:
		explicit WebSocketClient(const std::string& host,
								 const std::string& port,
								 const std::string& token);
 
		virtual ~WebSocketClient(void) noexcept = default;
 
		void connect(void);
 
		void disconnect(void);
 
		void send_system(const std::string& action,
						 const std::string& text);
 
		std::optional<json> read_response(void);
		
	private:
		std::string host;
 
		std::string port;
 
		std::string token;
 
		asio::io_context ioc;
 
		ssl::context ctx;
 
		std::optional<websocket::stream<beast::ssl_stream<tcp::socket>>> ws;
 
		bool connected = false;
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
