#ifndef FUNC_STR_H
#define FUNC_STR_H

#include <string>
#include <vector>

extern std::string TrimStr(const std::string & str);

extern int SplitStr(const std::string & str, char separator, std::vector<std::string> & result, bool ignoreEmpty = false);

template<typename T>
inline int SplitStrToNum(const std::string & str, char separator, std::vector<T> & result)
{
    static_assert(std::is_integral<T>::value, "T must be integral!");

    result.clear();
    std::vector<std::string> strVec;
    SplitStr(str, separator, strVec);
    T value = 0;
    for (const auto & iter : strVec) {
        value = (T)stoll(iter);
        result.emplace_back(value);
    }

    return result.size();
}

#endif //FUNC_STR_H
