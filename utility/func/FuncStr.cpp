#include "FuncStr.h"

std::string TrimStr(const std::string & str)
{
	std::string dest = str;
	if (!dest.empty()) {
		dest.erase(0, dest.find_first_not_of('\0'));
		dest.erase(dest.find_first_not_of('\0') + 1);

		dest.erase(0, dest.find_first_not_of(" \n\r\t"));
		dest.erase(dest.find_first_not_of(" \n\r\t") + 1);
	}
	return dest;
}

int SplitStr(const std::string & str, char separator, std::vector<std::string> & result, bool ignoreEmpty)
{
    result.clear();
    if (str.empty()) {
        return 0;
    }

    std::string subStr;
    int last = 0;
    int index = str.find_first_of(separator, last);
    while (index != std::string::npos)
    {
        subStr = str.substr(last, index - last);
        if (subStr.empty()) {
            if (!ignoreEmpty) {
                result.emplace_back(subStr);
            }
        } else {
            result.emplace_back(subStr);
        }

        last = index + 1;
        index = str.find_first_of(separator, last);
    }

    if (str.size() - last > 0)
    {
        subStr = str.substr(last, str.size() - last);
        result.emplace_back(subStr);
    }

    return result.size();
}
