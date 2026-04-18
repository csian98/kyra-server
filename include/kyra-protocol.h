/**
 * @file		kyra-protocol.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_PROTOCOL_H_
#define _HEADER_KYRA_PROTOCOL_H_

/* Include */

#include <cstdint>
#include <variant>
#include <string>
#include <vector>

#include <boost/beast/core/detail/base64.hpp>

#include <nlohmann/json.hpp>

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
	namespace b64 = boost::beast::detail::base64;
	
	using json = nlohmann::json;
	
	enum class InputOutputFormat {
		TEXT, AUDIO
	};

	enum class RequestType {
		PING, CHAT, SYSTEM, FILE, CODE
	};

	enum class ResponseType {
		PING, CHAT, SYSTEM, FILE, CODE
	};

	struct Content {
		std::vector<uint8_t> data;

		std::vector<std::string> images;	// base64

		static Content from_json(const json& j);

		void to_json(json& j) const;
	};

	struct PingRequestPayload {
		InputOutputFormat input_format = InputOutputFormat::TEXT;

		InputOutputFormat output_format = InputOutputFormat::TEXT;

	    bool location_sharing = false;

	    struct Option {
			double latitude = 0.0;

			double longitude = 0.0;
		} options;
	};

	struct SystemRequestPayload {
		std::string action;

		std::string text;
	};

	struct ChatRequestPayload {
		std::string model;

		InputOutputFormat input_format = InputOutputFormat::TEXT;

		InputOutputFormat output_format = InputOutputFormat::TEXT;

		bool stream = false;

		Content content;

		struct Option {
			float temperature = 0.2f;

			bool think_deep = false;
		} options;
	};

	struct FileRequestPayload {
		std::string action;

		std::string path;

		std::vector<uint8_t> data;
	};

	struct CodeRequestPayload {
		std::string action;

		std::string data;

		int cols = 80;

		int rows = 24;
	};

	using RequestPayload =
		std::variant<PingRequestPayload, SystemRequestPayload,
					 ChatRequestPayload, FileRequestPayload,
					 CodeRequestPayload>;
	
	struct Request {
		RequestType type;

		RequestPayload payload;

		static Request from_json(const json& j);

		json to_json(void) const;

		template <typename T>
		T& get(void) { return std::get<T>(this->payload); }

		template <typename T>
		const T& get(void) const { return std::get<T>(this->payload); }
	};

	struct PingResponsePayload {
		std::string text;
	};

	struct SystemResponsePayload {
		InputOutputFormat output_format = InputOutputFormat::TEXT;
		
		std::string action;

	    Content content;

		std::string text;
	};

	struct ChatResponsePayload {
		InputOutputFormat output_format = InputOutputFormat::TEXT;

		Content content;

		std::string text;
	};

	struct FileResponsePayload {
		std::string action;

		json metadata;

		std::vector<uint8_t> data;
	};

	struct CodeResponsePayload {
		std::string action;

		std::string data;

		int exit_code = -1;
	};

	using ResponsePayload =
		std::variant<PingResponsePayload, SystemResponsePayload,
					 ChatResponsePayload, FileResponsePayload,
					 CodeResponsePayload>;

	struct Response {
		ResponseType type;

		ResponsePayload payload;

		json to_json(void) const;

		template <typename T>
		T& get(void) { return std::get<T>(this->payload); }

		template <typename T>
		const T& get(void) const { return std::get<T>(this->payload); }
	};
}

/* Functions declaration */

namespace kyra {
	std::string extract_request(const Request& request);
	
	std::string extract_response(const Response& response);

	Response make_ping_response(const std::string& text = "pong");

	Response make_system_response(const std::string& action,
								  const std::string& text);

	Response make_chat_response(InputOutputFormat output_format,
								const std::string& text);

	Response make_file_response(const std::string& action,
								const json& metadata = {},
								std::vector<uint8_t> data = {});

	Response make_code_response(const std::string& action,
								const std::string& data = "",
								int exit_code = -1);

	json make_stream_start(void);

	json make_stream_token(const std::string& token, bool thinking = false);

	json make_stream_sentence_audio(const std::vector<uint8_t>& pcm);

	json make_stream_end(const std::string& full_text);

	std::string base64_encode(
		const std::vector<uint8_t>& data);

	std::vector<uint8_t> base64_decode(
		const std::string& encoded);
}

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
