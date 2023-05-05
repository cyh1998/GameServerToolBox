//
// Created by cuiyh on 2023/5/5.
//

#ifndef FUNC_MATH_H
#define FUNC_MATH_H

#include <stdint.h>
#include <vector>
#include "FuncUtil.h"

template<typename T>
class RandMgr
{
protected:
    struct SingleData
    {
        T data;
        uint32_t weight = 0;
        uint32_t add_weight = 0;
    };

public:
    RandMgr() = default;
    ~RandMgr() = default;

    // 添加数据和权重
    void Add(const T& data, const uint32_t weight)
    {
        SingleData sData;
        sData.data = data;
        sData.weight = weight;
        m_all_weight += weight;
        sData.add_weight = m_all_weight;
        m_vec.emplace_back(sData);
    }

    // 单个随机
    bool RandSingle(T& number)
    {
        if (m_all_weight <= 0) {
            return false;
        }

        uint32_t weigth = RandNumber(m_all_weight);
        for (const SingleData& data : m_vec)
        {
            if (data.add_weight > weigth) {
                number = data.data;
                return true;
            }
        }
        return false;
    }

    // 多个随机
    bool RandMore(std::vector<T>& ret, int count)
    {
        if (m_all_weight <= 0) {
            return false;
        }

        if (0 == count || m_vec.empty()) {
            return true;
        }
        ret.clear();
        ret.reserve(count);

        T number = 0;
        for (int i = 0; i < count; ++i) {
            RandSingle(number);
            ret.emplace_back(number);
        }
        return true;
    }

    // 多个随机(去重)
    bool RandMoreDedup(std::vector<T>& ret, int count)
    {
        if (m_all_weight <= 0) {
            return false;
        }

        if (0 == count || m_vec.empty()) {
            return true;
        }
        ret.clear();
        ret.reserve(count);

        if (count >= m_vec.size()) {
            for (const SingleData& data : m_vec) {
                ret.emplace_back(data.data);
            }
            return true;
        }

        std::vector<SingleData> temp;
        temp.assign(m_vec.begin(), m_vec.end());
        uint32_t weight = 0;
        uint32_t all_weight = m_all_weight;
        for (int i = 0; i < count; ++i)
        {
            if (all_weight <= 0 || temp.empty()) {
                return true;
            }

            weight = RandNumber(all_weight);
            for (auto iter = temp.begin(); iter != temp.end(); ++iter)
            {
                if (iter->add_weight > weight)
                {
                    all_weight -= iter->weight;
                    ret.emplace_back(iter->data);
                    temp.erase(iter);
                    break;
                }
            }
        }
    }

private:
    std::vector<SingleData> m_vec;
    uint32_t m_all_weight = 0;
};

#endif //FUNC_MATH_H
