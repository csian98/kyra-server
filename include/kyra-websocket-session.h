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

#include <mutex>
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

	struct SessionData;

	namespace session {
		extern std::map<unsigned int,
			std::pair<websocket::stream<beast::ssl_stream<tcp::socket>>*,
					  SessionData*>> clients;

		extern std::mutex mutex;
	}
	
	struct SessionData {
	    unsigned int session_id;

		std::vector<LLMMessage> short_term_memory;

		InputOutputFormat input_format = InputOutputFormat::TEXT,
			output_format = InputOutputFormat::TEXT;

		std::chrono::steady_clock::time_point timestamp;

		void update_timestamp(void);
	};
	
	class WebSocketSession {
	public:
		explicit WebSocketSession(beast::ssl_stream<tcp::socket> socket);

		virtual ~WebSocketSession(void) noexcept;

		void run(http::request<http::string_body> req);
		
	private:
		static void broadcast(const Response& text_response,
							  const Response& audio_response);
		
		websocket::stream<beast::ssl_stream<tcp::socket>> ws;

		std::shared_ptr<SessionData> session_data;
	};
}

/* Functions declaration */

namespace kyra {
	unsigned int get_session_id(void);
}

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
