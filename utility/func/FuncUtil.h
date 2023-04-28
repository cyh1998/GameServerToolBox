//
// Created by cuiyh on 2023/4/28.
//

#ifndef FUNC_UTIL_H
#define FUNC_UTIL_H

#include <random>
#include <type_traits>

inline std::mt19937& generator() {
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}

// Using std::is_integral_v<T> instead of std::is_integral<T>::value at C++17
template<typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
T RandNumber(T max) {
    std::uniform_int_distribution<T> dist(0, max);
    return dist(generator());
}

template<typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
T RandNumber(T min, T max) {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(generator());
}

template<typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
T RandNumber(T min, T max) {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(generator());
}

#endif //FUNC_UTIL_H
