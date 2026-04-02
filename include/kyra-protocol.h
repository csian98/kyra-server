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
		PING, CHAT, SYSTEM
	};

	enum class ResponseType {
		CHAT, SYSTEM
	};

	struct Image {
		std::vector<uint8_t> data;	// base64
	};

	struct Content {
		InputOutputFormat format;

		std::vector<uint8_t> data;	// base64

		std::vector<Image> images;
	};

	struct Request {
		RequestType type;

		std::string model;

		InputOutputFormat input_format;

		InputOutputFormat output_format;

		Content content;

		struct Option {
			float temperature = 0.2;
			
			bool think_deep = false;
		} options;

		static Request from_json(const json& j);

		json to_json(void) const;
	};

	struct Response {
		ResponseType type;

		InputOutputFormat output_format;

	    Content content;

		std::string text;

		json to_json(void) const;
	};
}

/* Functions declaration */

namespace kyra {
	std::string extract_text(const Request& request);

	// from text
	Response generate_response(
		const std::string& text,
		InputOutputFormat output_format,
		ResponseType type = ResponseType::CHAT);

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
