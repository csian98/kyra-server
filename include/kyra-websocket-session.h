/**
 * @file		kyra-websocket-session.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_WEBSOCKET_SESSION_H_
#define _HEADER_KYRA_WEBSOCKET_SESSION_H_

/* Include */

#include <thread>
#include <mutex>
#include <condition_variable>

#include <memory>
#include <chrono>

#include <string>
#include <set>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

#include <nlohmann/json.hpp>

#include "kyra-service.h"
#include "kyra-session-hub.h"
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
	namespace beast = boost::beast;
	namespace http = beast::http;
	namespace websocket = beast::websocket;

	using tcp = asio::ip::tcp;
	using json = nlohmann::json;
	
	class WebSocketSession {
	public:
		explicit WebSocketSession(beast::ssl_stream<tcp::socket> socket,
								  const UserSchema& user);

		virtual ~WebSocketSession(void) noexcept;

		void run(http::request<http::string_body> req);
		
	private:
		void reader_loop(void);

		void worker_loop(void);

		void send(const json& payload);
		
		websocket::stream<beast::ssl_stream<tcp::socket>> ws;

		uint64_t session_id = 0;

		std::queue<Request> queue;

		std::mutex write_mutex, queue_mutex;

		std::condition_variable cv;

		std::atomic<bool> closed{false};
	};
}

/* Functions declaration */


/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
