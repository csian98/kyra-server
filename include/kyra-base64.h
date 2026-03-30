/**
 * @file		kyra-base64.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_BASE64_H_
#define _HEADER_KYRA_BASE64_H_

/* Include */

#include <string>
#include <vector>
#include <cstdint>

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

/* Functions declaration */

namespace kyra {
	std::string base64_encode(const std::vector<uint8_t>& data);
	
	std::vector<uint8_t> base64_decode(const std::string& encoded_string);	
}

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
