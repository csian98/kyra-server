/**
 * @file		kyra-exception.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_LOGGER_H_
#define _HEADER_KYRA_LOGGER_H_

/* Include */

#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <source_location>

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include <algorithm>
#include <queue>
#include <string>
#include <string_view>

#include "kyra-exception.h"

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

/* defines typedef & constant */

/* MACRO functions */

#define KYRA_LOG_EX(ex)		::kyra::Logger::get_instance().log(ex)
#define KYRA_LOG_CURRENT	::kyra::Logger::get_instance().log_current()

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
	struct LoggerConfig {
		std::filesystem::path log_dir = "var/log";

		std::uintmax_t max_bytes = 10 * 1024 * 1024;

		int max_files = 5;

		bool async = true,
			echo_stderr = false;
	};

	class Logger {
	public:
		static Logger& get_instance(void);

		virtual ~Logger(void) noexcept;

		void log(const Exception& ex);

		void log(Severity severity, std::string_view message,
				 std::source_location location = std::source_location::current());

		void log_current(
			std::source_location location = std::source_location::current());

		void flush(void);

	private:
		Logger(void);

		Logger(const Logger&) = delete;

		Logger& operator=(const Logger&) = delete;

		void configure(LoggerConfig config);

		void open_log_file(void);

		void rotate_if_needed(void);

		void write_line(const std::string& line);

		void thread_function(void);

		LoggerConfig config;

		std::ofstream file;

		std::filesystem::path current_path;

		std::queue<std::string> queue;

		std::thread thread;
		
		std::mutex f_mutex, q_mutex;

		std::condition_variable cv;

		std::atomic<bool> is_running{false};
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
