/**
 * @file		kyra-session-hub.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_SESSION_HUB_H_
#define _HEADER_KYRA_SESSION_HUB_H_

/* Include */

#include <memory>
#include <functional>
#include <optional>
#include <chrono>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <string>
#include <vector>
#include <map>
#include <queue>

#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"
#include "boost/beast.hpp"
#include "boost/beast/ssl.hpp"

#include "nlohmann/json.hpp"

#include "kyra-database-handle.h"
#include "kyra-pre-retrieval.h"
#include "kyra-protocol.h"
#include "kyra-service.h"
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
	namespace websocket = beast::websocket;

	using tcp = asio::ip::tcp;
	using json = nlohmann::json;

	struct PendingMessage {
		PendingMessage(void) = default;

		PendingMessage(const std::string& role,
					   const std::string& content,
					   std::vector<std::string> images = {});
		
		std::string role;

		std::string content;

		std::vector<std::string> images;

		std::chrono::steady_clock::time_point enqueued_at;
	};

	class MessageQueue {
	public:
		MessageQueue(void) = default;

		void push(PendingMessage message);

		std::vector<PendingMessage> drain(void);

		std::vector<PendingMessage> try_drain(void);

		void shutdown(void);

		bool is_closed(void) const noexcept;

	private:
		std::vector<PendingMessage> drain_locked(void);

		std::queue<PendingMessage> queue;

		mutable std::mutex mutex;

		std::condition_variable cv;

		std::atomic<bool> closed{false};
	};
	
	struct SessionContext {
		uint64_t session_id = 0;

		UserSchema user;

		websocket::stream<beast::ssl_stream<tcp::socket>>* ws = nullptr;

		InputOutputFormat input_format = InputOutputFormat::TEXT;

		InputOutputFormat output_format = InputOutputFormat::TEXT;

		std::vector<Message> short_term_memory;

		std::shared_ptr<PreRetrieval> pre_retrieval;

	    MessageQueue pending;

		std::chrono::steady_clock::time_point timestamp;

		std::atomic<bool> processing{false};

		void update_timestamp(void);

		bool is_admin(void) const noexcept;
	};
	
	class SessionHub {
	public:
		static SessionHub& get_instance(void);

		void initialize(const DatabaseConfig& config);

		void shutdown(void);

		std::optional<UserSchema> authenticate(const std::string& token);

		std::optional<ProfileSchema> find_profile(uint64_t user_id);

	    uint64_t register_session(
			websocket::stream<beast::ssl_stream<tcp::socket>>* ws,
			const UserSchema& user, const ProfileSchema& profile);

		void unregister_session(uint64_t session_id);

		SessionContext* get_context(uint64_t session_id);

		void submit(uint64_t session_id,
					const std::string& role,
					const std::string& content,
					std::vector<std::string> images = {});

		size_t drain_and_append(uint64_t session_id);

		uint64_t append_chat_history(uint64_t session_id,
									 const std::string& role,
									 const std::string& content);

		void broadcast_system(const Response& text_response,
							  const Response& audio_response);

		void direct_message(const std::string& from_username,
							const std::string& to_username,
							const Response& text_response,
							const Response& audio_response);
		
	private:
		SessionHub(void) = default;

		std::map<uint64_t, std::unique_ptr<SessionContext>> sessions;

		std::mutex mutex;

		std::unique_ptr<DatabaseHandle> db;

		bool initialized = false;
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
