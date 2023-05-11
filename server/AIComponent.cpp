//
// Created by cuiyh on 2023/5/11.
//

#include "AIComponent.h"

AIComponent::AIComponent() {

}

AIComponent::~AIComponent() {

}

bool AIComponent::Init(std::string treeName)
{
    m_BTreeName = treeName;
    m_Agent = behaviac::Agent::Create<AIAgent>();
    bool bRet = m_Agent->btload(m_BTreeName);
    m_Agent->btsetcurrent(m_BTreeName);

    return false;
}

void AIComponent::UpdateLoop()
{
    behaviac::EBTStatus status = behaviac::BT_RUNNING;
    while (status == behaviac::BT_RUNNING) {
        status = m_Agent->btexec();
    }
}

void AIComponent::Cleanup()
{
    behaviac::Agent::Destroy(m_Agent);
}
