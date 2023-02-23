//
// Created by cuiyh on 2023/2/21.
//

#include <ctime>
#include <vector>
#include "FuncTime.h"
#include "FuncStr.h"

const char * formatStr[FormatType::FT_END] = {
    "%Y-%m-%d %H:&M:%S",
    "%Y-%m-%d",
    "%H:&M:%S"
};

std::string TimeToStr(FormatType eType, time_t nowTime)
{
    time_t timeValue = nowTime == 0 ? std::time(nullptr) : nowTime;

    tm tmSturct{};
    localtime_r(&timeValue, &tmSturct);

    char cStr[20] = {0};
    strftime(cStr, 20, formatStr[eType], &tmSturct);
    return cStr;
}

bool StrToTimeStamp(const std::string &timeStr, time_t &timeStamp)
{
    timeStamp = 0;
    tm tmSturct{};
    std::vector<std::string> vecDate;
    SplitStr(timeStr, ' ', vecDate);
    if (vecDate.size() < 2) {
        return false;
    } else {
        std::vector<int> vDate, vTime;
        SplitStrToNum(vecDate[0], '-', vDate);
        SplitStrToNum(vecDate[1], ':', vTime);
        if (vDate.size() < 3 || vTime.size() < 3) {
            return false;
        } else {
            tmSturct.tm_year = vDate[0] - 1900;
            tmSturct.tm_mon = vDate[1] - 1;
            tmSturct.tm_mday = vDate[2] - 1900;

            tmSturct.tm_hour = vTime[0];
            tmSturct.tm_min = vTime[1];
            tmSturct.tm_sec = vTime[2];
        }
    }
    timeStamp = mktime(&tmSturct);
    return true;
}

std::string GainMsecTimeStr()
{
    timespec tsSturct{};
    clock_gettime(CLOCK_REALTIME_COARSE, &tsSturct);
    time_t timer = tsSturct.tv_sec;

    tm tmSturct{};
    localtime_r(&timer, &tmSturct);
    char cStr[21] = {0};
    strftime(cStr, 21, "%Y-%m-%d %H:&M:%S.", &tmSturct);

    std::string timeStr = cStr;
    timeStr += std::to_string(tsSturct.tv_nsec / 1000000);
    return timeStr;
}
