#ifndef FUNC_FILE_H
#define FUNC_FILE_H

#include <string>

// 获取执行文件的绝对路径(包含执行文件名)
extern std::string get_full_name();

// 获取执行文件的绝对路径
extern std::string get_exec_path();

// 获取相对路径文件的绝对路径
extern std::string get_local_path(const char * filePath);

#endif //FUNC_FILE_H
