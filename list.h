//
// Created by bogdan on 13.12.2021.
//

#ifndef UNORDERED_MAP_LIST_H
#define UNORDERED_MAP_LIST_H

#include "list_iterator.h"

template<class T>
class list {
    std::shared_ptr<Node<T>> first = nullptr;
    std::shared_ptr<Node<T>> last = nullptr;
    size_t size;

public:

    list() : first(nullptr), last(nullptr), size(0) {};

    list(const list &oth) : size(0) {
        for (const auto &el: oth) {
            add(el);
        }
    };

    list(list &&oth) noexcept: size(oth.size) {
        first = oth.first;
        last = oth.last;
        oth.first = nullptr;
        oth.last = nullptr;
        oth.size = 0;
    }

    list &operator=(const list &oth) {
        clear();
        for (const auto &el: oth) {
            add(el);
        }
        return *this;
    };

    list &operator=(list &&oth) noexcept {
        clear();
        size = oth.size;
        first = oth.first;
        last = oth.last;
        oth.first = nullptr;
        oth.last = nullptr;
        oth.size = 0;
        return *this;
    }


    ~list() { clear(); };

    list_iterator<T> begin() const { return list_iterator<T>(first); };

    list_iterator<T> end() const { return list_iterator<T>(nullptr); };

    list_iterator<T> add(const T &ell) {
        if (last) {
            last->next = std::make_shared<Node<T>>(ell, nullptr, last);
            last = last->next;
        } else {
            first = std::make_shared<Node<T>>(ell, nullptr, nullptr);
            last = first;
        }
        ++size;
        return list_iterator<T>(last);
    };

    void pop() {
        if (size != 0) {
            last = last->prev;
            if (last) {
                last->next = nullptr;
            } else {
                first = nullptr;
            }
            --size;
        }
    };

    void clear() {
        while (size > 0) {
            pop();
        }
    };

    [[nodiscard]] bool empty() const { return size == 0; };

//    Node<T> *get_last() { return last.get(); };

    list_iterator<T> erase(list_iterator<T> pos) {
        if (pos.get() == nullptr) {
            return list_iterator<T>(nullptr);
        }
        if (pos.get() == first.get()) {
            first = first->next;
        } else {
            (pos - 1)->next = pos->next;
        }
        if (pos.get() == last.get()) {
            last = last->prev;
        } else {
            (pos + 1)->prev = pos->prev;
        }
        list_iterator<T> ans(pos.get()->next);
        --size;
        return ans;
    }

    void print() {
        for (const auto &el: *this) {
            std::cout << el << std::endl;
        }
    }

    size_t len() {
        return size;
    }
};

#endif //UNORDERED_MAP_LIST_H
