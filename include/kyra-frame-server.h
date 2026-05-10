/**
 * @file		kyra-frame-server.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_FRAME_SERVER_H_
#define _HEADER_KYRA_FRAME_SERVER_H_

/* Include */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include <string>
#include <vector>
#include <cstdint>

#include "curl/curl.h"

#include "kyra-protocol.h"
#include "kyra-pre-retrieval.h"
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
	class FrameServer {
	public:
		virtual ~FrameServer(void) noexcept;
		
		static FrameServer& get_instance(void);

		void start(const std::string& host = "127.0.0.1",
				   int port = 6336,
				   const std::string& script = "pylib/kyra_frame_server.py",
				   int ready_timeout_seconds = 180);

		void stop(void) noexcept;

		bool is_running(void) const noexcept;

		json process_frame(const std::vector<uint8_t>& image_data) const;

		json list_users(void) const;

		json get_user(const std::string& user_id) const;

		json create_user(const std::string& name,
						 const json& profile,
						 const std::vector<uint8_t>& image_data) const;

		json update_user(const std::string& user_id,
						 const std::string& name,
						 const json& profile) const;

		json delete_user(const std::string& user_id) const;

		json add_crop(const std::string& user_id,
					  const std::vector<uint8_t>& image_data) const;

		json delete_crop(const std::string& user_id,
						 const std::string& crop_id) const;
	private:
		FrameServer(void) = default;

		FrameServer(const FrameServer&) = delete;

		FrameServer& operator=(const FrameServer&) = delete;

		bool wait_until_ready(int timeout_seconds) const;

		std::string http_request(const std::string& method,
								 const std::string& path,
								 const std::string& body) const;

		pid_t pid;

		std::string host;

		int port = 0;
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
