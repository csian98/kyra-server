/**
 * @file		kyra-supertonic-engine.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_SUPERTONIC_ENGINE_H_
#define _HEADER_KYRA_SUPERTONIC_ENGINE_H_

/* Include */

#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <functional>
#include <algorithm>

#include "sherpa-onnx/c-api/c-api.h"
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
	class SupertonicEngine: public TTSEngine {
	public:
		using AudioSink =
			std::function<bool(const int16_t* pcm, std::size_t num_sampels)>;

		SupertonicEngine(const std::string& model_dir = "etc/weight/supertonic",
						 const std::string& voice_style = "etc/weight/supertonic/voice.bin",
						 bool int8 = true);

		virtual ~SupertonicEngine(void) noexcept;

		std::vector<uint8_t> synthesize(const std::string& text) override;

		std::vector<uint8_t> synthesize(const std::string& text,
										const AudioSink& on_chunk);

		int sample_rate(void) const noexcept override;

	private:
		std::string model_dir;

		std::string voice_style;

		std::string duration_predictor;

		std::string text_encoder;

		std::string vector_estimator;

		std::string vocoder;

		std::string tts_json;

		std::string unicode_indexer;

		int num_threads = 4;

		int speaker_id = 0;

		float speed = 1.2;

		float silence_scale = 0.2;

		int num_steps = 8;

		int sr = 44100;

		const SherpaOnnxOfflineTts* synth;
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
