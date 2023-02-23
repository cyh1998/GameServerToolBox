//
// Created by cuiyh on 2023/2/17.
//

#include <stdio.h>
#include <execinfo.h> //backtrace()
#include <cxxabi.h> //abi::__cxa_demangle()
#include "../func/FuncStr.h"
#include "CallStack.h"

#define BUFFERSIZE 2048

void CallStack::GetStack(char *buffer, size_t size)
{
    void *buffer_[128];
    int size_ = backtrace(buffer_, 128);
    int index = 0, ret = 0;
    char **stackInfo = backtrace_symbols(buffer_, size_);
    if (stackInfo == nullptr) {
        return;
    }

    for (int i = 0; i < size_; ++i)
    {
        char *name = nullptr, *indexBegin = nullptr, *indexEnd = nullptr;
        for (char *p = stackInfo[i]; *p; ++p)
        {
            if (*p == '(') {
                name = p;
            } else if (*p == '+') {
                indexBegin = p;
            } else if (*p == ')') {
                indexEnd = p;
                break;
            }
        }

        if (name && indexBegin && indexEnd && name < indexBegin)
        {
            *name++ = '\0';
            *indexBegin++ = '\0';
            *indexEnd++ = '\0';

            int status = 0;
            char *funcName = abi::__cxa_demangle(name, 0, 0, &status);
            if (status == 0) {
                ret = sprintf_s(buffer + index, size - index, "[bt]:(%u) %s : %s+%s%s\n", i, stackInfo[i], funcName, indexBegin, indexEnd);
            } else {
                ret = sprintf_s(buffer + index, size - index, "[bt]:(%u) %s : %s+%s%s\n", i, stackInfo[i], name, indexBegin, indexEnd);
            }

            free(funcName);
        } else {
            ret = sprintf_s(buffer + index, size - index, "[bt]:(%u) %s\n", i, stackInfo[i]);
        }

        if (ret > 0) {
            index += ret;
        }

        if (index + 0x128 > static_cast<int>(size)) {
            break;
        }
    }

    free(stackInfo);
}

void CallStack::GetStack(std::string &stackInfo) {
    stackInfo.clear();
    char stack[BUFFERSIZE] = {0};
    GetStack(stack, BUFFERSIZE);
    stackInfo.append(stack);
}

