#include <unistd.h> //getpagesize()
#include <stdint.h> //uint64
#include <string.h> //memcpy()
#include "HotFix.h"
#ifndef WIN32
#include <dlfcn.h> //dl相关api
#include <sys/mman.h> //mprotect()
#endif

int fix_func(const void* new_func, void* old_func)
{
#ifndef WIN32
	//跳转指令
    char prefix[] = {'\x48', '\xb8'};   //MOV new_func %rax
    char postfix[] = {'\xff', '\xe0'};  //JMP %rax

	//开启代码可写权限
    size_t page_size= getpagesize(); //获取系统内存分页大小
    char * align_point = static_cast<char *>(old_func) - (reinterpret_cast<uint64_t>(static_cast<char *>(old_func)) % page_size); //函数所在分页的起始地址

	const int inst_len = sizeof(prefix) + sizeof(void *) + sizeof(postfix); //写入指令的长度
	size_t len = static_cast<char *>(old_func) - align_point + inst_len; //新增跳转指令后函数的内存长度

	if (0 != mprotect(align_point, len, PROT_READ | PROT_WRITE | PROT_EXEC)) {
        return -1;
    }
	
	//将跳转指令写入原函数开头
    memcpy(old_func, prefix, sizeof(prefix));
    memcpy(static_cast<char *>(old_func) + sizeof(prefix), &new_func, sizeof(void *));
    memcpy(static_cast<char *>(old_func) + sizeof(prefix) + sizeof(void *), postfix, sizeof(postfix));

	//关闭代码可写权限
    if (0 != mprotect(align_point, len, PROT_READ | PROT_EXEC)) {
        return -1;
    }
#endif
    return 0;
}

int do_fix(const char* patch)
{
#ifndef WIN32
	// 调用dlopen加载so库
    void *lib = dlopen(patch, RTLD_NOW);
    if (nullptr == lib) {
        return -1;
    }
	
	// 查找函数符号表并且替换
    FIXTABLE * fix_item = (FIXTABLE *)dlsym(lib, "fix_table");
    if (nullptr == fix_item)  {
        dlclose(lib);
        return -1;
    }
    
    void * result = dlopen(nullptr, RTLD_NOW);
    if (nullptr == result) {
        dlclose(lib);
        return -1;
    }

    // 执行更新
    return fix_func(fix_item->new_func, fix_item->old_func);
#endif
    return 0;
}

