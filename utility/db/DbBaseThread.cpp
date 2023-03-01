//
// Created by cuiyh on 2023/3/1.
//

#include <ctime>
#include <chrono>
#include "DbBaseThread.h"

#define WARN_SIZE 2000

bool DbBaseThread::Init()
{
    m_thread = std::thread([this] { DbBaseThread::Update(this); });
    return false;
}

void DbBaseThread::UnInit()
{
    m_exit = true;
    if (m_thread.joinable()) {
        m_thread.join();
    }

    PopData();
}

void DbBaseThread::Update(void *arg)
{
    DbBaseThread *ptr = static_cast<DbBaseThread *>(arg);
    SimpleTimer<time_t> pingTimer(time(nullptr), 120);
    uint32_t sleepTime = 0;

    while (!ptr->m_exit)
    {
        if (pingTimer.Due(time(nullptr))) {
            ptr->DoPing();
        }

        if (!ptr->PopData()) {
            sleepTime = (sleepTime + 1) % 10 + 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        } else {
            sleepTime = 0;
        }
    }
}

bool DbBaseThread::PopData()
{
    std::list<std::string> dbRunList;
    std::unique_lock<std::mutex> lock(m_lock);
    if (m_dbOpList.empty()) {
        return false;
    }
    dbRunList.swap(m_dbOpList);
    lock.unlock();

    if (dbRunList.size() > WARN_SIZE) {
        // warn log
    }

    for (auto iter = dbRunList.begin(); iter != dbRunList.end(); )
    {
        ExecSql(*iter);
        iter = dbRunList.erase(iter);
    }
    dbRunList.clear();

    return true;
}

void DbBaseThread::PushData(const std::string &sqlStr)
{
    std::unique_lock<std::mutex> lock(m_lock);
    m_dbOpList.emplace_back(sqlStr);
}

