/**
 * @file		kyra-ttt-engine.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_TTT_ENGINE_H_
#define _HEADER_KYRA_TTT_ENGINE_H_

/* Include */

#include <memory>
#include <vector>
#include <string>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "kyra-mcp-engine.h"
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

	using StreamCallback =
		std::function<void(const std::string& token, bool thinking, bool done)>;

    struct Message {
		std::string role;

		std::string content;

		std::vector<std::string> images;

		json tool_calls;

		Message(void) = default;

		Message(const std::string& role,
				const std::string& content);

		bool has_image(void) const noexcept;

		bool has_tool_calls(void) const noexcept;
	};

	class TTTEngine {
	public:
		explicit TTTEngine(void);

		void attach_mcp_engine(std::shared_ptr<MCPEngine> mcp_engine);

		virtual std::vector<std::string> list_models(void) = 0;

		virtual std::string chat(const std::string& model,
								 std::vector<Message>& messages,
								 const float temperature = 0.8,
								 const bool think_deep = true) = 0;

		virtual std::string chat_stream(const std::string& model,
										std::vector<Message>& messages,
										StreamCallback cb,
										const float temperature = 0.8,
										const bool think_deep = true);

		std::vector<std::string> take_tool_images(void);	// most recent chat()/chat_stream()

	protected:
		virtual void truncate_messages(std::vector<Message>& messages);

		json format_tools(const std::vector<MCPTool>& tools);

		std::shared_ptr<MCPEngine> mcp_engine;

		json tools_format;

		std::vector<std::string> tool_images;

		int truncate_size = 25;
	};
}

/* Functions declaration */

namespace kyra {
    void update_messages(std::vector<Message>& messages,
						 const std::string& role,
						 const std::string& content,
						 std::vector<std::string> images = {},
						 json tool_calls = json());
}


/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
