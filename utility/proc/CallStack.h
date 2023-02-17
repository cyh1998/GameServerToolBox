//
// Created by cuiyh on 2023/2/17.
//

#ifndef CALLSTACK_H
#define CALLSTACK_H

#include <string>
#include "../base/Noncopyable.h"

class CallStack : Noncopyable
{
public:
    static void GetStack(char *buffer, size_t size);
    static void GetStack(std::string & stackInfo);
};

#endif //CALLSTACK_H
