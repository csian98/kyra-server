/**
 * @file		kyra-code-session.h
 * @author		Jeong Hoon (Sian) Choi
 */

//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_CODE_SESSION_H_
#define _HEADER_KYRA_CODE_SESSION_H_

/* Include */

#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <pty.h>
 
#include <string>
#include <array>
#include <deque>
 
#include "kyra-protocol.h"
#include "kyra-logger.h"
 
#include "kyra-protocol.h"
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
	class CodeSession {
	public:
		using OutputCallback = std::function<void(const std::string& data)>;
		
		using ExitCallback = std::function<void(int exit_code)>;
 
		CodeSession(void) = default;
		
		virtual ~CodeSession(void) noexcept;
 
		CodeSession(const CodeSession&) = delete;
		
		CodeSession& operator=(const CodeSession&) = delete;
 
		bool start(const std::string& container_name);
 
		void write(const std::string& data);
 
		void resize(uint16_t rows, uint16_t cols);
 
		void attach(void);
		
		void detach(void);
		
		void stop(void);
 
		bool is_running(void) const { return this->running.load(); }
		
		bool is_attached(void) const { return this->attached.load(); }
 
		void set_output_callback(OutputCallback cb);
		
		void set_exit_callback(ExitCallback cb);
 
	private:
		void read_loop(void);
		
		void wait_loop(void);
 
		std::string container_name;
 
		pid_t c_pid = -1;
		
		int master_fd = -1;
 
		std::atomic<bool> running{false};
		
		std::atomic<bool> attached{false};
 
		std::mutex write_mutex;
		
		std::mutex callback_mutex;
 
		OutputCallback output_cb;
		
		ExitCallback exit_cb;
 
		std::mutex buffer_mutex;
		
		std::deque<std::string> scrollback;
		
		static constexpr size_t max_buffer_size = 2000;
 
		std::thread read_thread;
		
		std::thread wait_thread;
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
