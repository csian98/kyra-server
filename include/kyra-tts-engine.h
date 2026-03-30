/**
 * @file		kyra-tts-engine.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_TTS_ENGINE_H_
#define _HEADER_KYRA_TTS_ENGINE_H_

/* Include */

#include <fstream>
#include <vector>
#include <regex>

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
	class TTSEngine {
	public:
		virtual ~TTSEngine(void) noexcept = default;

		virtual std::vector<uint8_t> synthesize(const std::string& text) = 0;
	};
}

/* Functions declaration */

namespace kyra {
	bool write_audio_data(const std::string& fname,
						  const std::vector<uint8_t>& audio_data);

	std::string strip_markdown(const std::string& text);
}

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
