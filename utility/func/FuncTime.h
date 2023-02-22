//
// Created by cuiyh on 2023/2/21.
//

#ifndef FUNC_TIME_H
#define FUNC_TIME_H

#include <string>

enum FormatType
{
    FT_ALL,      //2001-01-01 10:10:10
    FT_DATE,     //2001-01-01
    FT_TIME,     //10:10:10
    FT_END,
};

const int MINS  = 60;
const int HOURS = 60 * 60;
const int DAYS  = 60 * 60 * 24;
const int WEEKS = 60 * 60 * 24 * 7;

// 时间戳转字符串
extern std::string TimeToStr(FormatType eType = FT_ALL, time_t nowTime = 0);

// 字符串转时间戳
extern bool StrToTimeStamp(const std::string & timeStr, time_t & timeStamp);

// 获取毫秒级时间字符串 2001-01-01 10:10:10:001
extern std::string GainMsecTimeStr();

#endif //FUNC_TIME_H
