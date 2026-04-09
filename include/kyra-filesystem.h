/**
 * @file		kyra-filesystem.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_FILESYSTEM_H_
#define _HEADER_KYRA_FILESYSTEM_H_

/* Include */

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cstdint>
#include <cstdlib>

#include <vector>

#include "nlohmann/json.hpp"

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
	
	namespace fs = std::filesystem;

	struct FileEntry {
		std::string path;

		std::string type;	// "file", "dir"

		uint64_t size = 0;

		uint64_t modified = 0;
	};

	class FileSystem {
	public:
		explicit FileSystem(const std::string& base_root = "filesystem");

		void ensure_user_dir(const std::string& username);

		json list_tree(const std::string& username);

		json read_file(const std::string& username,
					   const std::string& relative_path);

		std::vector<uint8_t> read_file_binary(const std::string& username,
											  const std::string& relative_path,
											  std::string& out_filename,
											  std::string& out_mime_type);
		
		bool save_file(const std::string& username,
					   const std::string& relative_path,
					   const std::vector<uint8_t>& data);

		std::vector<uint8_t> zip_directory(
			const std::string& username, const std::string& relative_path);

	private:
		fs::path resolve_safe(const std::string& username,
							  const std::string& relative_path);

		void collect_entries(const fs::path& root,
							 const fs::path& current,
							 std::vector<FileEntry>& entries);

		static std::string guess_mime_type(const std::string& ext);

		std::string base_root;
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
