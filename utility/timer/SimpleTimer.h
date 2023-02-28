//
// Created by cuiyh on 2023/2/28.
//

#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

template<typename T>
class SimpleTimer
{
public:
    SimpleTimer() = default;
    virtual ~SimpleTimer() = default;

    SimpleTimer(T value, T interval) :
        m_value(value),
        m_interval(interval) {}

    bool Due(T current) {
        if (0 == m_value) {
            m_value = current;
        }

        if (current >= static_cast<T>(m_value + m_interval)) {
            m_value = current;
            return true;
        }
        return false;
    }

    T GetValue() const { return m_value; }
    T GetInterval() const { return m_interval; }
    void SetValue(T value = 0) { m_value = value; }
    void SetInterval(T interval) { m_interval = interval; }

protected:
    T m_value {0};
    T m_interval {0};
};

#endif //SIMPLE_TIMER_H
