//
// Created by cuiyh on 2023/3/1.
//

#ifndef DB_BASE_THREAD_H
#define DB_BASE_THREAD_H

#include <list>
#include <string>
#include <mutex>
#include <thread>
#include "../timer/SimpleTimer.h"

class DbBaseThread
{
public:
    DbBaseThread() = delete;
    virtual ~DbBaseThread() = delete;

public:
    virtual bool Init();
    virtual void UnInit();
    static void Update(void *arg);

    virtual bool PopData();
    virtual void PushData(const std::string & sqlStr);

    virtual void DoPing() = 0;
    virtual uint64_t ExecSql(const std::string & sqlStr) = 0;

protected:
    std::list<std::string> m_dbOpList;
    std::mutex m_lock;
    std::thread m_thread;
    SimpleTimer<int> m_timer;
    bool m_exit {false};
};

#endif //DB_BASE_THREAD_H
