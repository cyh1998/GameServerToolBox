#ifndef FUNC_STR_H
#define FUNC_STR_H

#include <string>
#include <vector>

#define sprintf_s sprintf_safe

// 去除字符串首位特殊字符
extern std::string TrimStr(const std::string & str);

// 根据分隔符分割字符串，返回分割的字符串个数
// str 源字符串
// separator 分隔符
// result 分割结果
// ignoreEmpty 是否忽略空值
extern int SplitStr(const std::string & str, char separator, std::vector<std::string> & result, bool ignoreEmpty = false);

// 根据分隔符分割字符串为整数类型
template<typename T>
inline int SplitStrToNum(const std::string & str, char separator, std::vector<T> & result)
{
    static_assert(std::is_integral<T>::value, "T must be integral!");

    result.clear();
    std::vector<std::string> strVec;
    SplitStr(str, separator, strVec);
    T value = 0;
    for (const auto & iter : strVec) {
        value = static_cast<T>(stoll(iter));
        result.emplace_back(value);
    }

    return result.size();
}

// 安全格式化字符串函数
template<typename... Args>
inline int sprintf_safe(char * dst, size_t size, const char * format, Args&&... args)
{
    int len = snprintf(dst, size, format, std::forward<Args>(args)...);
    dst[size - 1] = 0;
    return len > static_cast<int>(size) ? static_cast<int>(size) : len;
}

#endif //FUNC_STR_H
