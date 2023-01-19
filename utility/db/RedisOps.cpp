//
// Created by cuiyh on 2023/1/17.
//

#include "RedisOps.h"

RedisOps::RedisOps() {

}

RedisOps::~RedisOps() {
    if (m_context) {
        ::redisFree(m_context);
    }
    m_context = nullptr;
}

bool RedisOps::init(const std::string & ip, uint16_t port, const std::string & pwd, uint32_t timeOut) {
    m_ip = ip;
    m_port = port;
    m_pwd = pwd;
    m_timeOut = timeOut;

    return reConnect();
}

bool RedisOps::reConnect() {
    if (!m_timeOut) {
        return connectWithTimeout();
    } else {
        return connect();
    }
}

bool RedisOps::connect() {
    if (m_context) ::redisFree(m_context);

    m_context = ::redisConnect(m_ip.c_str(), m_port);
    if (nullptr == m_context) {
        return false;
    } else if (m_context->err) {
        redisFree(m_context);
        m_context = nullptr;
        return false;
    }
    return true;
}

bool RedisOps::connectWithTimeout() {
    if (m_context) ::redisFree(m_context);

    timeval tmv{};
    tmv.tv_sec = m_timeOut;
    tmv.tv_usec = 0;

    m_context = ::redisConnectWithTimeout(m_ip.c_str(), m_port, tmv);
    if (nullptr == m_context) {
        return false;
    } else if (m_context->err) {
        redisFree(m_context);
        m_context = nullptr;
        return false;
    }
    return true;
}

void RedisOps::close() {
    if (nullptr == m_context) return;

    redisFree(m_context);
    m_context = nullptr;
}


