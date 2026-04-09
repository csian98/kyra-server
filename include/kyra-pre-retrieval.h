/**
 * @file		kyra-pre-retrieval.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_PRE_RETRIEVAL_H_
#define _HEADER_KYRA_PRE_RETRIEVAL_H_

/* Include */

#include <sstream>
#include <memory>
#include <iomanip>
#include <chrono>
#include <ctime>

#include <string>
#include <vector>

#include <thread>

#include "curl/curl.h"
#include "nlohmann/json.hpp"

#include "kyra-database-schema.h"
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
	using json = nlohmann::json;

	struct MemoryEntry {
		std::string id;

		std::string memory;

		double score = 0.0;
	};
	
	struct PreRetrievalConfig {
		PreRetrievalConfig(const UserSchema& user,
						   const ProfileSchema& profile);

		std::string user_id;

		std::string username;

		std::string display_name;

		std::string system_prompt;

		std::string time_zone;	// IANA: America/Los_Angeles, Asia/Seoul

		std::string fullname;

		std::string birthday;
	};

	class PreRetrieval {
	public:
		explicit PreRetrieval(const PreRetrievalConfig& config);

		virtual ~PreRetrieval(void) noexcept = default;

		std::string build(const std::string& query, int limit = 0) const;

		std::vector<MemoryEntry> search_memories(
			const std::string& query, int limit = 0) const;

		void store_memory(const std::string& content) const;

		void store_conversation(
			const std::vector<std::pair<
			std::string, std::string>>& messages) const;

		void store_conversation_async(
			const std::vector<std::pair<
			std::string, std::string>>& messages) const;

	private:
		std::string time_context(void) const;

		std::string memory_context(const std::string& query,
								   int limit) const;

		std::string http_get(const std::string& endpoint) const;

		std::string http_post(const std::string& endpoint,
							  const json& data) const;
		
		PreRetrievalConfig config;

		std::string memory_host = "http://127.0.0.1:6335";
	};
}

/* Functions declaration */

namespace kyra {
	size_t pre_retrieval_write_cb(void* contents, size_t size,
								  size_t nmemb, std::string* userp);
}

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
