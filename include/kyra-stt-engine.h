/**
 * @file		kyra-stt-engine.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_STT_ENGINE_H_
#define _HEADER_KYRA_STT_ENGINE_H_

/* Include */

#include <cstdint>
#include <vector>

#include "mackron/miniaudio.h"
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
	class STTEngine {
	public:
		virtual ~STTEngine(void) noexcept = default;

		virtual std::string transcribe(const std::vector<uint8_t>& audio_data,
									   const int sample_rate = 16000,
									   const int channels = 1) = 0;
	};
}

/* Functions declaration */

namespace kyra {
	bool read_audio_data(const std::string& fname,
						 std::vector<float>& pcmf32,
						 std::vector<std::vector<float>>& pcmf32s,
						 bool stereo);
}

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
