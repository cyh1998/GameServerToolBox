//
// Created by cuiyh on 2023/3/10.
//

#ifndef MYSQL_OPS_H
#define MYSQL_OPS_H

#include <string>
#include <vector>
#include "mysql++/mysql++.h"

using namespace mysqlpp;

class MysqlOps
{
public:
    MysqlOps();
    MysqlOps(const std::string &host, const std::string &user,
            const std::string & pwd, const std::string &dbName, int port);
    ~MysqlOps();

public:
    bool Connect();
    void DisConnect() { m_mysql.disconnect(); }
    bool Connected() { return m_mysql.connected(); }

    int64_t DbExec(const char *sql);
    bool DbExec(std::vector<std::string> &vecSql);

    std::string GetHost() { return m_strHost; }
    std::string GetUser() { return m_strUser; }
    std::string GetPassword() { return m_strPassword; }
    std::string GetDbName() { return m_strDbName; }
    void SetDbName(const std::string & name) { m_strDbName = name; }
    int GetPort() const { return m_port; }

    bool DbPing();

private:
    static bool IsErrorNum(int errorNum);

private:
    Connection m_mysql;

    uint32_t m_port{};
    std::string m_strHost;
    std::string m_strUser;
    std::string m_strPassword;
    std::string m_strDbName;
};

#endif //MYSQL_OPS_H
