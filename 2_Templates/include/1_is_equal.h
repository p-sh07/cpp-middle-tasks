//
// Created by Pavel on 17.10.2025.
//

#pragma once
#include <print>

// Определите шаблон is_equal с двумя типовыми
// параметрами. В шаблоне нужно корректно проверять две переменные на равенство
template <typename T1, typename T2>
bool is_equal(const T1& val1, const T2& val2) {
    return val1 == val2;
}

//Перегрузка шаблона функции для работы с указателями
template <typename T1, typename T2>
bool is_equal(T1* val1, T2* val2) {
    //check ptrs are not null
    assert(val1);
    assert(val2);

    return *val1 == *val2;
}

//Функция для сравнения чисел с плавающей точкой
inline bool is_equal(double val1, double val2, double epsilon) {
    return val1 - val2 < epsilon;
}

//Перегрузка для двух double
inline bool is_equal(double val1, double val2) {
    return is_equal(val1, val2, 1e-7);
}

//Перегрузка для float & double
inline bool is_equal(double val1, float val2) {
    return is_equal(val1, static_cast<double>(val2), 1e-5);
}

inline bool is_equal(float val1, double val2) {
    return is_equal(static_cast<double>(val1), val2, 1e-5);
}

//Перегрузка для float
inline bool is_equal(float val1, float val2) {
    return is_equal(static_cast<double>(val1), static_cast<double>(val2), 1e-5);
}