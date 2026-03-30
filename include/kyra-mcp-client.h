/**
 * @file		kyra-mcp-client.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_MCP_CLIENT_H_
#define _HEADER_KYRA_MCP_CLIENT_H_

/* Include */

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <string>

#include <curl/curl.h>
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
	using json = nlohmann::json;

	struct MCPTool {
		std::string name;

		std::string description;

		json input_schema;
	};

	struct MCPResource {
		std::string uri;

		std::string name;

		std::string description;

		std::string mime_type;
	};

	class MCPClient {
	public:
		MCPClient(const std::string& command);

		virtual ~MCPClient(void) noexcept;

		bool initialize(void);

		json query(const std::string& method,
				   const json& params);

		std::vector<MCPTool> list_tools(void);

		json call_tool(const std::string& name,
					   const json& arguments);

		std::vector<MCPResource> list_resources(void);

		std::string read_resource(const std::string& uri);
		
	private:
		bool start_mcp_server(void);

		void stop_mcp_server(void);

		json read(void);

		void write(const json& request);
		
		std::string mcp_command;

		int pid;;

		int stdin_pipe[2];
		
		int stdout_pipe[2];

		bool initialized;
	};
}

/* Functions declaration */

// void swap(Sample&, Sample&) noexcept;

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
