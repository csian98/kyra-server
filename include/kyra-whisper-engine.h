/**
 * @file		kyra-whisper-engine.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_WHISPER_ENGINE_H_
#define _HEADER_KYRA_WHISPER_ENGINE_H_

/* Include */

#include <vector>

#include "kyra-stt-engine.h"
#include "whisper/whisper.h"

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
	class WhisperEngine: public STTEngine {
	public:
		WhisperEngine(const std::string& model_path =
					  "etc/weight/whisper/ggml-large-v3-turbo.bin");

		virtual ~WhisperEngine(void) noexcept;

		std::string transcribe(const std::vector<float>& pcm_data,
							   const int sample_rate = WHISPER_SAMPLE_RATE,
							   const int channels = 1);
		
		std::string transcribe(const std::vector<uint8_t>& audio_data,
							   const int sample_rate = WHISPER_SAMPLE_RATE,
							   const int channels = 1) override;

	private:
		bool initialize(void);

		void cleanup(void);

		std::string inner_transcribe(const std::vector<float>& pcmf32);

		bool is_initialized = false;
		
		std::string model_path;

		void* context;
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
