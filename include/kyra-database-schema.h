/**
 * @file		kyra-database-schema.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_DATABASE_SCHEMA_H_
#define _HEADER_KYRA_DATABASE_SCHEMA_H_

/* Include */

#include <string>
#include <cstdint>

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
	struct UserSchema {
		uint64_t id;

		std::string role;

		std::string username;

		std::string token;

		std::string display_name;

		std::string created_at;

		std::string updated_at;
	};

	struct ContactSchema {
		uint64_t id;

		uint64_t uid;

		std::string platform;

		std::string handle;

		bool is_primary;

		bool is_verified;

		std::string updated_at;
	};

	struct DocumentSchema {
		uint64_t id;

		uint64_t uid;

		std::string file_name;

		uint64_t file_size;

		std::string mime_type;

		std::string file_hash;

		std::string updated_at;
	};

	struct SessionHistorySchema {
		uint64_t id;

		uint64_t uid;

		std::string started_at;

		std::string ended_at;
	};

	struct ChatHistorySchema {
		uint64_t id;

		uint64_t session_id;

		std::string role;

		std::string content;

		std::string created_at;
	};

	struct ToolCallHistorySchema {
		uint64_t id;

		uint64_t chat_id;

		std::string tool_name;

		std::string tool_input;

		std::string tool_output;

		std::string status;

		uint32_t duration_ms;

		std::string created_at;
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
