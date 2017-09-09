#include "str_helper.h"
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <stdarg.h>

namespace Helper
{
	string str_helper::UrlDecode(const std::string& szToDecode)
	{
		std::string result;
		int hex = 0;
		for (size_t i = 0; i < szToDecode.length(); ++i)
		{
			switch (szToDecode[i])
			{
			case '+':
				result += ' ';
				break;
			case '%':
				if (isxdigit(szToDecode[i + 1]) && isxdigit(szToDecode[i + 2]))
				{
					std::string hexStr = szToDecode.substr(i + 1, 2);
					hex = strtol(hexStr.c_str(), 0, 16);
					//字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@]  
					//可以不经过编码直接用于URL  
					if (!((hex >= 48 && hex <= 57) || //0-9  
						(hex >= 97 && hex <= 122) ||   //a-z  
						(hex >= 65 && hex <= 90) ||    //A-Z  
													   //一些特殊符号及保留字[$-_.+!*'(),]  [$&+,/:;=?@]  
						hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
						|| hex == 0x2a || hex == 0x2b /*|| hex == 0x2c*/ || hex == 0x2d || hex == 0x2e /*|| hex == 0x2f*/
						/*|| hex == 0x3A */ || hex == 0x3B /*|| hex == 0x3D*/ || hex == 0x3f || hex == 0x40 || hex == 0x5f
						))
					{
						result += char(hex);
						i += 2;
					}
					else result += '%';
				}
				else {
					result += '%';
				}
				break;
			default:
				result += szToDecode[i];
				break;
			}
		}
		return result;
	}

	/*
	string 转换为 wstring
	*/
	std::wstring str_helper::c2w(const char *pc)
	{
		std::wstring val = L"";

		if (NULL == pc)
		{
			return val;
		}
		//size_t size_of_ch = strlen(pc)*sizeof(char);  
		//size_t size_of_wc = get_wchar_size(pc);  
		size_t size_of_wc;
		size_t destlen = mbstowcs(0, pc, 0);
		if (destlen == (size_t)(-1))
		{
			return val;
		}
		size_of_wc = destlen + 1;
		wchar_t * pw = new wchar_t[size_of_wc];
		mbstowcs(pw, pc, size_of_wc);
		val = pw;
		delete pw;
		return val;
	}


	std::wstring str_helper::s2w(std::string from)
	{
		return c2w(from.c_str());
	}

	/*
	wstring 转换为 string
	*/
	std::string str_helper::w2c(const wchar_t * pw)
	{
		std::string val = "";
		if (!pw)
		{
			return val;
		}
		size_t size = wcslen(pw) * sizeof(wchar_t);
		char *pc = NULL;
		if (!(pc = (char*)malloc(size)))
		{
			return val;
		}
		size_t destlen = wcstombs(pc, pw, size);
		/*转换不为空时，返回值为-1。如果为空，返回值0*/
		if (destlen == (size_t)(0))
		{
			return val;
		}
		val = pc;
		delete pc;
		return val;
	}

	std::string str_helper::w2s(std::wstring from)
	{
		return w2s(from.c_str());
	}

	std::string str_helper::string_format(const std::string fmt_str, ...) 
	{
		int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
		std::unique_ptr<char[]> formatted;
		va_list ap;
		while (1) {
			formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
			strcpy(&formatted[0], fmt_str.c_str());
			va_start(ap, fmt_str);
			final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
			va_end(ap);
			if (final_n < 0 || final_n >= n)
				n += abs(final_n - n + 1);
			else
				break;
		}
		return std::string(formatted.get());
	}

	// trim from start (in place)
	 void str_helper::ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
	}

	// trim from end (in place)
	 void str_helper::rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	}

	// trim from both ends (in place)
	 void str_helper::trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

	// trim from start (copying)
	 std::string str_helper::ltrim_copy(std::string s) {
		ltrim(s);
		return s;
	}

	// trim from end (copying)
	 std::string str_helper::rtrim_copy(std::string s) {
		rtrim(s);
		return s;
	}

	// trim from both ends (copying)
	 std::string str_helper::trim_copy(std::string s) {
		trim(s);
		return s;
	}

	 std::string str_helper::replace_all(std::string str, std::string old_value, std::string new_value)
	 {
		 while (true) {
			 string::size_type   pos(0);
			 if ((pos = str.find(old_value)) != string::npos)
				 str.replace(pos, old_value.length(), new_value);
			 else
				 break;
		 }
		 return str;
	 }

	 std::vector<std::string> str_helper::Split(std::string& str, const char* c)
	 {
		 char *cstr, *p;
		 std::vector<std::string> res;
		 cstr = new char[str.size() + 1];
		 strcpy(cstr, str.c_str());
		 p = strtok(cstr, c);
		 while (p != NULL)
		 {
			 res.push_back(p);
			 p = strtok(NULL, c);
		 }
		 delete[] cstr;
		 return res;
	 }
}
