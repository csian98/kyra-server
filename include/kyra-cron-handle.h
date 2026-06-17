/**
 * @file		kyra-cron-handle.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_CRON_HANDLE_H_
#define _HEADER_KYRA_CRON_HANDLE_H_

/* Include */

#include <chrono>
#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <optional>
#include <functional>

#include <unistd.h>
#include <sys/wait.h>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <nlohmann/json.hpp>

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

	using time_point = std::chrono::system_clock::time_point;

	struct CronSchedule {
		std::vector<int> minutes;	// 0-59

		std::vector<int> hours;		// 0-23

		std::vector<int> days;		// 1-31

		std::vector<int> months;	// 1-12

		std::vector<int> weeks;		// 0-6, 0: Sunday

		std::string raw;			// * * * * *

		bool matches(const std::tm& local) const noexcept;

		static bool parse(const std::string& spec, CronSchedule& out);
	};

	struct CronTask {
		std::size_t id;

		CronSchedule schedule;

		std::string username;

		std::string action;

		std::string text;

		std::string timezone;	// IANA tz

		time_point next_run;

		int remain = -1;

		bool operator>(const CronTask& other) const noexcept {
			return this->next_run > other.next_run;
		}

		std::string serialize(void) const;

		static bool parse_line(const std::string& line, CronTask& out);
	};

	class CronHandle {
	public:
		using TimezoneResolver =
			std::function<std::optional<std::string>(const std::string& username)>;

		static CronHandle& get_instance(void) noexcept;

		CronHandle(const CronHandle&) = delete;

		CronHandle& operator=(const CronHandle&) = delete;
		
		void set_timezone_resolver(TimezoneResolver resolver);

		bool initialize(
			const std::string& crontab_path,
			const std::string& request_binary = "bin/kyra-system-request.elf");

		void start(void);

		void stop(void) noexcept;

		std::vector<CronTask> list_tasks(const std::string& username);

		std::size_t add_task(const std::string& line,
							 const std::string& username);

		bool remove_task(std::size_t id,
						 const std::string& username);

		bool reload(void);

	private:
		CronHandle(void) noexcept;

		virtual ~CronHandle(void) noexcept;

		void handle_cron_task(void);

		bool load_locked(void);

		bool persist_locked(void) const;

		void execute_async(const CronTask& task) const;
		
		std::string resolve_timezone(const std::string& username) const;

		time_point compute_next_run(const CronSchedule& schedule,
									time_point from,
									const std::string& timezone) const;

		std::string crontab_path;

		std::string request_binary;

		TimezoneResolver tz_resolver;

		mutable std::mutex mtx;

		std::condition_variable cv;

		std::priority_queue<CronTask,
							std::vector<CronTask>,
							std::greater<CronTask>> queue;

		std::map<std::size_t, CronTask> registry;

		std::set<std::size_t> alive;

		std::size_t next_id;

		std::thread handler;

		std::atomic<bool> running;

		std::atomic<bool> initialized;
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
