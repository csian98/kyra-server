/**
 * @file		kyra-database-handle.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_DATABASE_HANDLE_H_
#define _HEADER_KYRA_DATABASE_HANDLE_H_

/* Include */

#include <memory>
#include <functional>
#include <chrono>
#include <cstdint>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <vector>
#include <string>
#include <queue>

#include <optional>

#include "mariadb/conncpp.hpp"
#include "openssl/rand.h"
#include "openssl/evp.h"

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
	struct DatabaseConfig {
		std::string host = "127.0.0.1";

		unsigned int port = 3306;

		std::string user = "kyra";

		std::string password;

		std::string database = "kyra";

		unsigned int pool_size = 4;
	};

	class DatabaseConnectionPool {
	public:
		explicit DatabaseConnectionPool(const DatabaseConfig& config);

		virtual ~DatabaseConnectionPool(void) noexcept = default;

		DatabaseConnectionPool(const DatabaseConnectionPool&) = delete;

		DatabaseConnectionPool& operator=(const DatabaseConnectionPool&) = delete;

		std::unique_ptr<sql::Connection> acquire(void);

		void release(std::unique_ptr<sql::Connection> conn);

	private:
		std::unique_ptr<sql::Connection> create_connection(void);

		DatabaseConfig config;

		sql::Driver* driver;

		std::queue<std::unique_ptr<sql::Connection>> pool;

		std::mutex mutex;

		std::condition_variable cv;
	};

	class DatabaseScopedConnection {
	public:
		explicit DatabaseScopedConnection(DatabaseConnectionPool& pool);

		virtual ~DatabaseScopedConnection(void) noexcept;

		DatabaseScopedConnection(const DatabaseScopedConnection&) = delete;

		DatabaseScopedConnection&
		operator=(const DatabaseScopedConnection&) = delete;

		sql::Connection* get(void) const noexcept;

		sql::Connection* operator->(void) const noexcept;

	private:
		DatabaseConnectionPool& pool;

		std::unique_ptr<sql::Connection> conn;
	};

	class DatabaseHandle {
	public:
		explicit DatabaseHandle(const DatabaseConfig& config);

		virtual ~DatabaseHandle(void) noexcept = default;

		DatabaseHandle(const DatabaseHandle&) = delete;

		DatabaseHandle& operator=(const DatabaseHandle&) = delete;

		// kyra.users
		std::pair<uint64_t, std::string> create_user(const std::string& username,
													 const std::string& display_name = "",
													 const std::string& role = "user");

		std::optional<UserSchema> find_user_by_token(const std::string& token);

		std::optional<UserSchema> find_user_by_username(const std::string& username);

		std::string recreate_user_token(uint64_t user_id);

		bool update_user_role(uint64_t user_id, const std::string& role);
		
		bool update_user_display_name(uint64_t user_id,
									  const std::string& display_name);

		bool delete_user(uint64_t user_id);

		// kyra.profile
		std::optional<ProfileSchema> find_profile_by_uid(uint64_t uid);
		
	    bool update_profile_fullname(uint64_t uid, const std::string& fullname);

		bool update_profile_system_prompt(uint64_t uid, const std::string& system_prompt);

		bool update_profile_time_zone(uint64_t uid, const std::string& time_zone);

		bool update_profile_language(uint64_t uid, const std::string& language);

		bool update_profile_birthday(uint64_t uid, const std::string& birthday);

		// kyra.calendars
		uint64_t create_calendar(uint64_t uid,
								 const std::string& handle,
								 const std::string& label = "",
								 bool writable = false);
		
		std::vector<CalendarSchema> find_calendars_by_uid(uint64_t uid);

		bool update_calendar_handle(uint64_t calendar_id, const std::string& handle);

		bool update_calendar_label(uint64_t calendar_id, const std::string& label);

		bool set_calendar_writable(uint64_t calendar_id, bool writable);

		bool delete_calendar(uint64_t calendar_id);

		// kyra.contacts
		uint64_t create_contact(uint64_t uid,
								const std::string& platform,
								const std::string& handle,
								bool is_primary = false,
								bool is_verified = false);

		std::vector<ContactSchema> find_contacts_by_uid(uint64_t uid);

		bool update_contact_handle(uint64_t contact_id, const std::string& handle);

		bool verify_contact(uint64_t contact_id);

		bool set_contact_primary(uint64_t contact_id, bool is_primary);
		
		bool delete_contact(uint64_t contact_id);

		// kyra.documents

		uint64_t create_document(uint64_t uid,
								 const std::string& file_name,
								 uint64_t file_size,
								 const std::string& mime_type,
								 const std::string& file_hash);

		std::vector<DocumentSchema> find_documents_by_uid(uint64_t uid);

		std::optional<DocumentSchema> find_document_by_hash(const std::string& file_hash);

		bool delete_document(uint64_t document_id);

		// kyra.session_history

		uint64_t open_session(uint64_t uid);

		bool close_session(uint64_t session_id);

		std::optional<SessionHistorySchema> find_session_by_id(uint64_t session_id);

		std::vector<SessionHistorySchema> find_sessions_by_uid(uint64_t uid,
															   uint32_t limit = 50);

		// kyra.chat_history

		uint64_t insert_chat(uint64_t session_id,
							 const std::string& role,
							 const std::string& content);

		std::vector<ChatHistorySchema> find_chats_by_session(uint64_t session_id,
															 uint32_t limit = 200);
		
	private:
		static std::string generate_token(void);

		static std::string sha256(const std::string& input);

		DatabaseConnectionPool connection;
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
