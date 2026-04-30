/**
 * @file		kyra-memory-server.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_MEMORY_SERVER_H_
#define _HEADER_KYRA_MEMORY_SERVER_H_

/* Include */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "curl/curl.h"

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
	class MemoryServer {
	public:
		static MemoryServer& get_instance(void);

		void start(const std::string& host = "127.0.0.1",
				   int port = 6335,
				   const std::string& script = "pylib/kyra_memory_server.py",
				   int ready_timeout_seconds = 120);

		void stop(void) noexcept;

		bool is_running(void) const noexcept;

		virtual ~MemoryServer(void) noexcept;

	private:
		MemoryServer(void) = default;

		MemoryServer(const MemoryServer&) = delete;

		MemoryServer& operator=(const MemoryServer&) = delete;

		bool wait_until_ready(int timeout_seconds) const;

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
