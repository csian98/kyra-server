/**
 * @file		kyra-piper-engine.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_PIPER_ENGINE_H_
#define _HEADER_KYRA_PIPER_ENGINE_H_

/* Include */

#include <vector>

#include "piper/piper.h"
#include "kyra-tts-engine.h"
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
	class PiperEngine: public TTSEngine {
	public:
		PiperEngine(const std::string& model_path =
					"etc/weight/piper/en_US-amy-low.onnx",
					const std::string& config_path =
					"etc/weight/piper/en_US-amy-low.onnx.json",
					const std::string& espeak_path =
					"etc/weight/piper/espeak-ng-data");

		virtual ~PiperEngine(void) noexcept;

		std::vector<uint8_t> synthesize(const std::string& text) override;

	private:
		std::string model_path;

		std::string config_path;

		std::string espeak_path;

		int speaker_id = 0;

		float length_scale = 1.0;

		piper_synthesizer* synth;
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
