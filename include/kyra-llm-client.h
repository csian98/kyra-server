/**
 * @file		kyra-llm-client.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_LLM_CLIENT_H_
#define _HEADER_KYRA_LLM_CLIENT_H_

/* Include */

#include <memory>
#include <vector>
#include <string>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "kyra-mcp-client.h"
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

	struct LLMImage {
		std::vector<uint8_t> data;

		LLMImage(void) = default;

		explicit LLMImage(std::vector<uint8_t> bytes);

		bool is_empty(void) const noexcept;
	};
	
	struct LLMMessage {
		std::string role;	// "user", "assistant", "system"

		std::string content;

		std::vector<LLMImage> images;

		LLMMessage(void) = default;

		LLMMessage(const std::string& role, const std::string& conent);

		void add_image(std::vector<uint8_t> bytes);

		bool has_image(void) const noexcept;
	};

	class LLMClient {
	public:
		explicit LLMClient(void);
		
		void attach_mcp_client(std::shared_ptr<MCPClient> mcp_client);

		virtual std::vector<std::string> list_models(void) = 0;

		virtual std::string generate(const std::string& model,
									 const std::string& prompt,
									 const std::vector<LLMImage>& images = {},
									 const float temperature = 0.6,
									 const bool think = true) = 0;

		virtual std::string chat(const std::string& model,
								 std::vector<LLMMessage>& messages,
								 const float temperature = 0.6,
								 const bool think = true) = 0;
	protected:
		virtual void truncate_messages(std::vector<LLMMessage>& messages);
		
		json format_tools(const std::vector<MCPTool>& tools);
		
		std::shared_ptr<MCPClient> mcp_client;

		json tools_format;

		int truncate_size = 10;
	};
}

/* Functions declaration */

namespace kyra {
    void update_messages(std::vector<LLMMessage>& messages,
						 const std::string& role,
						 const std::string& content,
						 std::vector<LLMImage> images = {});
}


/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
