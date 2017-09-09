#pragma once
#ifndef STR_HELPER
#define STR_HELPER

#include <string>
#include <string.h>
#include <vector>
#include <memory>
using namespace std;

namespace Helper
{
	class str_helper
	{
	public:
		static std::string UrlDecode(const std::string& szToDecode);
		static std::wstring c2w(const char *pc);
		static std::wstring s2w(std::string from);
		static std::string w2c(const wchar_t * pw);
		static std::string w2s(std::wstring from);
		static std::string string_format(const std::string fmt_str, ...);
		static void ltrim(std::string &s);
		static void rtrim(std::string &s);
		static void trim(std::string &s);
		static std::string ltrim_copy(std::string s);
		static std::string rtrim_copy(std::string s);
		static std::string trim_copy(std::string s);
		static std::string replace_all(std::string str, std::string old_value, std::string new_value);
		static std::vector<std::string> Split(std::string& str, const char* c);
	};
}

#endif // !STR_HELPER