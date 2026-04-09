/**
 * @file		kyra-service.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_SERVICE_H_
#define _HEADER_KYRA_SERVICE_H_

/* Include */

#include <memory>
#include <mutex>

#include "kyra-tts-engine.h"
#include "kyra-stt-engine.h"
#include "kyra-tts-engine.h"

#include "kyra-ollama-engine.h"
#include "kyra-whisper-engine.h"
#include "kyra-piper-engine.h"

#include "kyra-protocol.h"
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
	class Service {
	public:
		static Service& get_instance(void);

		Request speech_to_text(Request&& request);
		
		Response text_to_text(Request&& request);
		
		Response text_to_text(Request&& request,
							  std::vector<Message>& messages);
		
		Response text_to_speech(Response&& response);
		
	private:
		explicit Service(void);

		Service(const Service&) = delete;

		Service& operator=(const Service&) = delete;
		
		std::mutex stt_mutex, ttt_mutex, tts_mutex;

		std::shared_ptr<STTEngine> stt_engine;

		std::shared_ptr<TTTEngine> ttt_engine;

		std::shared_ptr<TTSEngine> tts_engine;
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
