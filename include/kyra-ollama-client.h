/**
 * @file		kyra-ollama-client.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_OLLAMA_CLIENT_H_
#define _HEADER_KYRA_OLLAMA_CLIENT_H_

/* Include */

#include <vector>
#include <string>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "kyra-llm-client.h"
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
	using json = nlohmann::json;
	
	class OllamaClient: public LLMClient {
	public:
		OllamaClient(const std::string& host =
					 "http://localhost:11434");

		virtual ~OllamaClient(void) noexcept;

		virtual std::vector<std::string> list_models(void) override;

		virtual std::string generate(const std::string& model,
									 const std::string& prompt,
									 const std::vector<LLMImage>& images = {},
									 const float temperature = 0.6,
									 const bool think = true) override;

		virtual std::string chat(const std::string& model,
								 std::vector<LLMMessage>& messages,
								 const float temperature = 0.6,
								 const bool think = true) override;

	private:
		virtual void truncate_messages(
			std::vector<LLMMessage>& messages) override;

		json message_to_json(const LLMMessage& msg) const;
		
		std::string http_get(const std::string& endpoint);
		
		std::string http_post(const std::string& endpoint,
							  const json& data);
		
		std::string host;
	};
}

/* Functions declaration */

namespace kyra {
	static size_t write_callback(void*, size_t, size_t, std::string*);
}

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
