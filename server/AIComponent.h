//
// Created by cuiyh on 2023/5/11.
//

#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

// #include "base/Singleton.h"
#include <string>
#include "behaviac_generated/types/behaviac_types.h"

class AIComponent
{
public:
    AIComponent();
    ~AIComponent();

    bool Init(std::string treeName);
    void UpdateLoop();
    void Cleanup();

// 提供给behaviac的接口
public:

private:
    std::string m_BTreeName;
    AIAgent* m_Agent = nullptr;
};

#endif //AI_COMPONENT_H
