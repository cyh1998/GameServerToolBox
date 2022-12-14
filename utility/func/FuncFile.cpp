#include <unistd.h>
#include <string.h>
#include "FuncFile.h"

// 获取执行文件的绝对路径(包含执行文件名)
std::string get_full_name()
{
	static std::string strResult;
	if (!strResult.empty()) {
		return strResult;
	}

	char path[1024] = {0};
	if (readlink("/proc/self/exe", path, sizeof(path)) < 0) {
		return "";
	}

	strResult = path;
	return strResult;
}

// 获取执行文件的绝对路径
std::string get_exec_path() 
{
	static std::string strResult;
	if (!strResult.empty()) {
		return strResult;
	}

	std::string strTemp = get_full_name();
	auto ret = strrchr(strTemp.c_str(), '/');

	if (nullptr == ret) {
		return "";
	}

	strResult.append(strTemp.c_str(), (ret - strTemp.c_str()));
	return strResult;
}

// 获取相对路径文件的绝对路径
std::string get_local_path(const char * filePath)
{
	std::string ret = get_exec_path();
	ret += "/";
	ret += filePath;
	return ret;
}

