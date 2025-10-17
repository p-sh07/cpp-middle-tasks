//
// Created by Pavel on 17.10.2025.
//

#pragma once
#include <memory>
#include <print>

//А.Шаблон типа
template <typename T>
T error_value;

//Полная специализация для int
template <>
int error_value<int> = -1;

//Частичные специализации для указателей
template <typename T>
const T* error_value<T*> = nullptr;

template <typename T>
const std::unique_ptr<T> error_value<std::unique_ptr<T>> = nullptr;

//Б.Шаблон класса
template<typename T>
class Span {
public:
    /* определите зависимые типы reference, const_reference, pointer, const_pointer, size_type здесь */
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

    template<typename It>
    Span(It first, size_type count);

    template<typename It1, typename It2>
    Span(It1 first, It2 last);

    reference operator[](size_type idx);
    const_reference operator[](size_type idx) const;

    bool empty() const;

    pointer data();
    const_pointer data() const;

    size_type size() const;

    Span subspan(size_type offset, size_type count) {
        return Span{data_ + offset, count};
    }

private:
    pointer data_;
    size_type size_;
};

template<typename T>
Span<const std::byte> as_bytes(Span<T> span);

template <class T>
Span<const std::byte> as_bytes(Span<T> span);

template <typename T>
template <typename It>
Span<T>::Span(It first, size_type count) : data_{std::to_address(first)}, size_{count} {}

template <typename T>
template <typename It1, typename It2>
Span<T>::Span(It1 first, It2 last)
    : data_{std::to_address(first)}, size_{static_cast<size_type>(std::distance(first, last))} {}

template <typename T>
Span<T>::reference Span<T>::operator[](size_type idx) {
    return data_[idx];
}

template <typename T>
Span<T>::const_reference Span<T>::operator[](size_type idx) const {
    return data_[idx];
}

template <typename T>
bool Span<T>::empty() const {
    return size_ == 0;
}

template <typename T>
Span<T>::pointer Span<T>::data() {
    return data_;
}

template <typename T>
Span<T>::const_pointer Span<T>::data() const {
    return data_;
}

template <typename T>
Span<T>::size_type Span<T>::size() const {
    return size_;
}

template <class T>
Span<const std::byte> as_bytes(Span<T> span) {
    return {reinterpret_cast<const std::byte *>(span.data()), span.size() * sizeof(T)};
}