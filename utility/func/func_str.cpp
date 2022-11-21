#include "func_str.h"

//去除字符串首位特殊字符
extern std::string trim_str(const std::string & str)
{
	std::string dest = str;
	if (!dest.empty()) {
		dest.erase(0, dest.find_first_not_of('\0'));
		dest.erase(dest.find_first_not_of('\0') + 1);

		dest.erase(0, dest.find_first_not_of(' \n\r\t'));
		dest.erase(dest.find_first_not_of(' \n\r\t') + 1);
	}
	return dest;
}
