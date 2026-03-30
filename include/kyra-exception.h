/**
 * @file		kyra-exception.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_EXCEPTION_H_
#define _HEADER_KYRA_EXCEPTION_H_

/* Include */

#include <exception>
#include <optional>
#include <chrono>

#include <source_location>
#include <string>
#include <string_view>

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
	using system_clock = std::chrono::system_clock;
	
	using time_point = system_clock::time_point;
	
	enum class Severity {
		Info = 0,
	    Warning = 1,
		Critical = 2,
		Fatal = 3
	};
	
	class Exception : public std::exception {
	public:
		Exception(Severity severity, const std::string& message,
				  std::source_location loc = std::source_location::current());

		std::string format(void) const;
		
	private:
		Severity severity;

		std::string message;

		std::source_location location;

		std::optional<std::error_code> ec;

		time_point timestamp;
	};
}

/* Functions declaration */

namespace kyra {
	std::string_view to_string(Severity s) noexcept;
}

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
