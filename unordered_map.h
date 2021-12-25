// Copyright 2021 Bogdan Shumilishskiy bshumilishsky@mail.ru

#ifndef TEMPLATE_UNORDERED_MAP1_H
#define TEMPLATE_UNORDERED_MAP1_H

#include <utility>
#include <memory>
#include "iterator.h"

template<class Key, class T, class Hash, class EqualKey>
class unordered_map {
    size_t len;
    size_t bucket_count = 2;
    size_t max_load = 2;
    std::shared_ptr<list<std::pair<Key, T>>[]> data;

public:
    unordered_map() : len(0), data(new list<std::pair<Key, T>>[bucket_count]) {}

    unordered_map(const unordered_map &oth) noexcept
            : len(oth.len),
              bucket_count(oth.bucket_count),
              max_load(oth.max_load),
              data(new list<std::pair<Key, T>>[oth.bucket_count]) {
        for (size_t i = 0; i < bucket_count; ++i) {
            data[i] = oth.data[i];
        }
    }

    unordered_map &operator=(const unordered_map &oth) noexcept {
        len = oth.len;
        bucket_count = oth.bucket_count;
        max_load = oth.max_load;
        data.reset(new list<std::pair<Key, T>>[oth.bucket_count]);
        for (size_t i = 0; i < bucket_count; ++i) {
            data[i] = oth.data[i];
        }
        return *this;
    }

    unordered_map(unordered_map &&oth)  noexcept : len(oth.len), bucket_count(oth.bucket_count), max_load(oth.max_load),
                                         data(oth.data) {
        oth.len = 0;
        oth.bucket_count = 0;
        oth.max_load = 0;
        oth.data = nullptr;
    };

    unordered_map &operator=(unordered_map &&oth)  noexcept {
        len = oth.len;
        bucket_count = oth.bucket_count;
        max_load = oth.max_load;
        data = oth.data;
        oth.len = 0;
        oth.bucket_count;
        oth.max_load = 0;
        oth.data = nullptr;
        return *this;
    }

    [[nodiscard]] size_t size() const noexcept { return len; };

    [[nodiscard]] bool empty() const noexcept { return len == 0; };

    iterator<std::pair<Key, T>> begin() {
        for (size_t i = 0; i < bucket_count; ++i) {
            if (!data[i].empty()) {
                return iterator<std::pair<Key, T>>(data[i].begin().get(), data.get() + i, data.get(),
                                                   data.get() + bucket_count);
            }
        }
        return iterator<std::pair<Key, T>>(nullptr, nullptr, data.get(), data.get() + bucket_count);
    }


    iterator<std::pair<Key, T>> end() const noexcept {
        list<std::pair<Key, T>> *map_end = data.get() + bucket_count;
        return iterator<std::pair<Key, T>>(nullptr, map_end - 1, data.get(), map_end);
    }

    T &at(const Key &key_m) {
        size_t buck_num = Hash{}(key_m) % bucket_count;
        for (auto &it: data[buck_num]) {
            if (EqualKey{}(std::get<0>(it), key_m)) {
                return std::get<1>(it);
            }
        }
        throw std::out_of_range("Out of range in unordered_map::at");
    }

    void rehash(size_t count) {
        auto new_data = std::shared_ptr<list<std::pair<Key, T>>[]>(new list<std::pair<Key, T>>[count]);
        size_t buck_num;
        for (const auto &it: *this) {
            buck_num = Hash{}(std::get<0>(it)) % count;
            new_data[buck_num].add(it);
        }
        data = std::move(new_data);
        bucket_count = count;
    }

    iterator<std::pair<Key, T>> insert(const Key &key_m,
                                       const T &value) noexcept {
        size_t buck_num = Hash{}(key_m) % bucket_count;
        for (auto it = data[buck_num].begin(); it != data[buck_num].end(); ++it) {
            if (EqualKey{}(std::get<0>(*it), key_m)) {
                return iterator<std::pair<Key, T>>(it.get(), data.get() + buck_num, data.get(),
                                                   data.get() + bucket_count);
            }
        }
        ++len;
        if (len + 1 > max_load * bucket_count) {
            rehash(2 * bucket_count);
        }
        auto it = data[buck_num].add(std::pair<Key, T>(key_m, value));
        return iterator<std::pair<Key, T>>(it.get(), data.get() + buck_num, data.get(),
                                           data.get() + bucket_count);
    }

    iterator<std::pair<Key, T>> erase(iterator<std::pair<Key, T>> pos) noexcept {
        auto buck = pos.get_buck();
        list_iterator<std::pair<Key, T>> l_it(buck->begin());
        while (l_it.get() != pos.get()) {
            ++l_it;
        }
        l_it = buck->erase(l_it);
        --len;
        return iterator<std::pair<Key, T>>(l_it.get(), buck, data.get(),
                                           data.get() + bucket_count);
    }

    T &operator[](const Key &key_m) noexcept {
        size_t buck_num = Hash{}(key_m) % bucket_count;
        for (auto &it: data[buck_num]) {
            if (EqualKey{}(std::get<0>(it), key_m)) {
                return std::get<1>(it);
            }
        }
        auto ans = insert(key_m, T());
        return std::get<1>(*ans);
    }

    void swap(unordered_map &oth) noexcept {
        std::swap(len, oth.len);
        std::swap(bucket_count, oth.bucket_count);
        std::swap(max_load, oth.max_load);
        std::swap(data, oth.data);
    }

    iterator<std::pair<Key, T>> find(const Key &key_m) noexcept {
        size_t buck_num = Hash{}(key_m) % bucket_count;
        for (auto it = data[buck_num].begin(); it != data[buck_num].end(); ++it) {
            if (EqualKey{}(std::get<0>(*it), key_m)) {
                return iterator<std::pair<Key, T>>(it.get(), data.get() + buck_num, data.get(),
                                                   data.get() + bucket_count);
            }
        }
        return end();
    }

    void print() {
        for (const auto &pos: *this) {
            std::cout << std::get<0>(pos) << "  " << std::get<1>(pos) << std::endl;
        }
    }
};

#endif  // TEMPLATE_UNORDERED_MAP1_H