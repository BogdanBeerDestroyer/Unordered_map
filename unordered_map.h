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
    }

    unordered_map(unordered_map &&) = delete;

    unordered_map &operator=(unordered_map &&) = delete;

//    iterator<std::pair<Key, T>> begin() const {
//        auto ptr = data;
//        while (ptr.get() != data.get() + bucket_count && ptr->empty()) {
//            ptr.reset(ptr.get() + 1);
//        }
//        return iterator<std::pair<Key, T>>();
    //return iterator<std::pair<Key, T>>((ptr->begin()).get(), ptr.get(), data.get(), data.get() + bucket_count);
//        return iterator<std::pair<Key, T>>(std::shared_ptr<Node<std::pair<Key, T>>>((ptr->begin()).get()), ptr,
//                                           data, std::shared_ptr<Node<std::pair<Key, T>>>(data.get() + bucket_count));
//    }

//    iterator<std::pair<Key, T>> begin() const {
//        for (size_t i = 0; i < bucket_count; ++i) {
//            if (!data[i].empty()) {
//                return iterator<std::pair<Key, T>>(data[i].)
//            }
//        }
//    }

//    iterator<std::pair<Key, T>> end() const noexcept {
//        list<std::pair<Key, T>> *map_end = data.get() + bucket_count;
//        return iterator<std::pair<Key, T>>(nullptr, map_end - 1, data.get(), map_end);
//    }

//    iterator<std::pair<Key, T>> begin() noexcept {
//        for (size_t i = 0; i < bucket_count; ++i) {
//            if (!data[i].empty()) {
//                return iterator<std::pair<Key, T>>()
//            }
//        }

        [[nodiscard]] size_t size() const noexcept { return len; };

        [[nodiscard]] bool empty() const noexcept { return len == 0; };

//    T &at(const Key &key_m) {
//        size_t buck_num = Hash{}(key_m) % bucket_count;
//        for (const auto &it: data[buck_num]) {
//            if (EqualKey{}(std::get<0>(it), key_m)) {
//                return std::get<1>(it);
//            }
//        }
//        throw std::out_of_range("Out of range in unordered_map::at");
//    }
//
//    void rehash(size_t count) {
//        auto new_data = std::make_shared<list<std::pair<Key, T>>>(count);
//        size_t buck_num;
//        for (const auto &it: *this) {
//            buck_num = Hash{}(std::get<0>(it)) % count;
//            new_data[buck_num].add(it);
//        }
//        data = std::move(new_data);
//        bucket_count = count;
//    }
//
//    iterator<std::pair<Key, T>> insert(const Key &key_m,
//                                       const T &value) noexcept {
//        size_t buck_num = Hash{}(key_m) % bucket_count;
//        //for (auto &it: data[buck_num]) {
//        for (auto it = data[buck_num].begin(); it != data[buck_num].end(); ++it) {
//            if (EqualKey{}(std::get<0>(*it), key_m)) {
//                return iterator<std::pair<Key, T>>(it.get(), data.get() + buck_num, data.get(),
//                                                   data.get() + bucket_count);
//            }
//        }
//        if (len + 1 > max_load * bucket_count) {
//            rehash(2 * bucket_count);
//        }
//        buck_num = Hash{}(key_m) % bucket_count;
//        ++len;
//        auto it = data[buck_num].add(std::pair<Key, T>(key_m, value));
//        return iterator<std::pair<Key, T>>(it.get(), data.get() + buck_num, data.get(),
//                                           data.get() + bucket_count);
//    }
//
//    iterator<std::pair<Key, T>> erase(iterator<std::pair<Key, T>> pos) noexcept {
//        list_iterator<std::pair<Key, T>> it(pos.get());
//        auto buck = std::make_shared<list<std::pair<Key, T>>>(pos.get_buck());
//        it = buck->erase(it);
//        --len;
//        return iterator<std::pair<Key, T>>(it.get(), buck, data,
//                                           data + bucket_count);
//    }
//
//    T &operator[](const Key &key_m) noexcept {
//        size_t buck_num = Hash{}(key_m) % bucket_count;
//        for (auto &it: data[buck_num]) {
//            if (EqualKey{}(std::get<0>(it), key_m)) {
//                return std::get<1>(it);
//            }
//        }
//        auto ans = insert(key_m, T());
//        return std::get<1>(*ans);
//    }
//
//    void swap(unordered_map &oth) noexcept {
//        std::swap(len, oth.len);
//        std::swap(bucket_count, oth.bucket_count);
//        std::swap(max_load, oth.max_load);
//        std::swap(data, oth.data);
//    }

//    iterator<std::pair<Key, T>> find(const Key &key_m) noexcept {
//        size_t buck_num = Hash{}(key_m) % bucket_count;
//        for (const auto &it: data[buck_num]) {
//            if (EqualKey{}(std::get<0>(*it), key_m)) {
//                return iterator<std::pair<Key, T>>(it.get(), &data[buck_num], data,
//                                                   data + bucket_count);
//            }
//        }
//        return end();
//    }

//    void print() {
//        for (const auto &pos: *this) {
//            std::cout << std::get<0>(pos) << "  " << std::get<1>(pos) << std::endl;
//        }
//    }
    };

#endif  // TEMPLATE_UNORDERED_MAP1_H