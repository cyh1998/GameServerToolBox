//
// Created by cuiyh on 2023/3/10.
//

#include <thread>
#include <chrono>
#include "../func/FuncStr.h"
#include "MysqlOps.h"

MysqlOps::MysqlOps() = default;

MysqlOps::MysqlOps(const std::string &host, const std::string &user,
        const std::string &pwd, const std::string &dbName, int port) :
        m_strHost(host),
        m_strUser(user),
        m_strPassword(pwd),
        m_strDbName(dbName),
        m_port(port)
{
}

MysqlOps::~MysqlOps() = default;

bool MysqlOps::Connect()
{
    try {
        m_mysql.disable_exceptions();
        m_mysql.disconnect();
        m_mysql.set_option(new SetCharsetNameOption("utf8"));
        m_mysql.set_option(new ConnectTimeoutOption(30)); //second

        if (m_mysql.connect(m_strDbName.c_str(), m_strHost.c_str(),
                m_strUser.c_str(), m_strPassword.c_str(), m_port))
        {
            m_mysql.query("SET NAMES utf8");
            return true;
        }
        m_mysql.enable_exceptions();
    } catch (Exception &e) {
        // error log
    }
    return false;
}

int64_t MysqlOps::DbExec(const char *sql)
{
    for (int i = 0; i < 60; ++i)
    {
        int64_t rows = 0;
        try
        {
            SimpleResult res;
            Query query = m_mysql.query();
            query << sql;

            res = query.execute();
            if (!res)
            {
                int errorNum = m_mysql.errnum();
                if (0 == errorNum || 1312 == errorNum) {
                    return 0;
                }

                if (IsErrorNum(query.errnum())) {
                    if (!DbPing()) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    }
                } else {
                    return -1;
                }
            } else {
                rows = static_cast<int64_t>(res.rows());
                return rows;
            }
        } catch (Exception &e) {
            if (!DbPing()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
    }

    return -1;
}

bool MysqlOps::DbExec(std::vector<std::string> &vecSql)
{
    for (int i = 0; i < vecSql.size(); ++i)
    {
        std::string strSql = vecSql[i];
        strSql = TrimStr(strSql);
        if (strSql.empty()) {
            continue;
        }
        DbExec(strSql.c_str());
    }
    return true;
}

bool MysqlOps::DbPing()
{
    if (!m_mysql.ping())
    {
        // error log
        return Connect();
    }
    return true;
}

bool MysqlOps::IsErrorNum(int errorNum)
{
    return 1042 == errorNum || 1043 == errorNum || 1081 == errorNum
           || (errorNum >= 1158 && errorNum <= 1162) || 1218 == errorNum
           || 1430 == errorNum || errorNum >= 2000;
}

