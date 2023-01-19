//
// Created by cuiyh on 2023/1/17.
//

#ifndef REDISOPS_H
#define REDISOPS_H

#include <string>
#include "hiredis/hiredis.h"

class RedisOps
{
public:
    RedisOps();
    ~RedisOps();

    bool init(const std::string & ip, uint16_t port, const std::string & pwd, uint32_t timeOut = 0);
    void close(); //redisFree

    template<typename... Args>
    redisReply* runCommand(const char *format, Args &&... args); //redisCommand

private:
    bool reConnect();
    bool connect(); //redisConnect
    bool connectWithTimeout(); //redisConnectWithTimeout

public:
    std::string m_ip;
    std::string m_pwd;
    uint16_t m_port;
    uint32_t m_timeOut {0}; //超时时间(秒)

    redisContext* m_context {nullptr};
};

template<typename... Args>
redisReply *RedisOps::runCommand(const char *format, Args &&... args) {
    redisReply *reply = nullptr;
    reply = (redisReply *)::redisCommand(m_context, format, std::forward<Args>(args)...);
    if (nullptr == reply) {
        reConnect();
    } else if(REDIS_REPLY_ERROR == reply->type) {
        ::freeReplyObject(reply);
    }
    return reply;
}

#endif //REDISOPS_H
