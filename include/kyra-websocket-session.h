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
#include <filesystem>

#include <string>
#include <set>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

#include <nlohmann/json.hpp>

#include "kyra-service.h"
#include "kyra-filesystem.h"
#include "kyra-pre-retrieval.h"
#include "kyra-session-hub.h"
#include "kyra-code-session.h"
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
	namespace fs = std::filesystem;

	using tcp = asio::ip::tcp;
	using json = nlohmann::json;
	
	class WebSocketSession {
	public:
		explicit WebSocketSession(beast::ssl_stream<tcp::socket> socket,
								  const UserSchema& user,
								  const ProfileSchema& profile);

		virtual ~WebSocketSession(void) noexcept;

		void run(http::request<http::string_body> req);
		
	private:
		void reader_loop(void);

		void worker_loop(void);

		void watchdog_loop(void);

		void handle_system_request(const Request& request,
								   SessionContext* ctx);

		void handle_file_request(const Request& request,
								 SessionContext* ctx);

		void handle_code_request(const Request& request,
								 SessionContext* ctx);

		void send(const json& payload);

		void send_binary(const std::vector<uint8_t>& data);
		
		websocket::stream<beast::ssl_stream<tcp::socket>> ws;

		uint64_t session_id = 0;

		std::queue<Request> queue;

		std::mutex write_mutex, queue_mutex, watchdog_mutex;

		std::condition_variable cv, watchdog_cv;

		std::atomic<bool> closed{false};

		std::unique_ptr<CodeSession> code_session;
		
		FileSystem u_fs;
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
