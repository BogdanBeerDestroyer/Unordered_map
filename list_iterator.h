//
// Created by bogdan on 13.12.2021.
//

#ifndef UNORDERED_MAP_LIST_ITERATOR_H
#define UNORDERED_MAP_LIST_ITERATOR_H

#include <iterator>
#include <memory>

template<class T>
struct Node {
    T val;
    std::shared_ptr<Node<T>> next = nullptr;
    std::shared_ptr<Node<T>> prev = nullptr;

    Node(T val_m, std::shared_ptr<Node<T>> next_m, std::shared_ptr<Node<T>> prev_m) : val(val_m), next(next_m),
                                                                                      prev(prev_m) {};
};

template<class T>
class list_iterator : public std::iterator<std::random_access_iterator_tag, T> {
    std::shared_ptr<Node<T>> ptr = nullptr;

public:

    explicit list_iterator(const std::shared_ptr<Node<T>> &ptr_m) : ptr(ptr_m) {}

    list_iterator<T> &operator++() {
        if (ptr) {
            ptr = ptr->next;
        }
        return *this;
    }

    list_iterator<T> operator++(int) {
        list_iterator it1(*this);
        if (ptr) {
            ptr = ptr->next;
        }
        return it1;
    }

    list_iterator<T> &operator--() {
        if (ptr) {
            ptr = ptr->prev;
        }
        return *this;
    }

    list_iterator<T> operator--(int) {
        list_iterator it1(*this);
        if (ptr) {
            ptr = ptr->prev;
        }
        return it1;
    }

    list_iterator<T> &operator+=(size_t value) {
        for (size_t i = 0; i < value; ++i) {
            if (ptr) {
                ptr = ptr->next;
            }
        }
        return *this;
    }

    list_iterator<T> &operator-=(size_t value) {
        for (size_t i = 0; i < value; ++i) {
            if (ptr) {
                ptr = ptr->prev;
            }
        }
        return *this;
    }

    Node<T> *get() { return ptr.get(); }

    T &operator*() { return ptr->val; }

    const T &operator*() const { return ptr->val; }

    std::shared_ptr<Node<T>> operator->() { return ptr; }

    bool operator==(const list_iterator &oth) { return oth.ptr == ptr; }

    // bool null() { return ptr == nullptr; };
};

template<class T>
list_iterator<T> operator+(list_iterator<T> it, size_t value) {
    it += value;
    return it;
}

template<class T>
list_iterator<T> operator-(list_iterator<T> it, size_t value) {
    it -= value;
    return it;
}

template<class T>
bool operator!=(list_iterator<T> it1, const list_iterator<T> &it2) {
    return !(it1 == it2);
}

#endif //UNORDERED_MAP_LIST_ITERATOR_H
