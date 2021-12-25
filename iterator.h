// Copyright 2021 Bogdan Shumilishskiy bshumilishsky@mail.ru

#ifndef TEMPLATE_ITERATOR_H
#define TEMPLATE_ITERATOR_H

#endif  // TEMPLATE_ITERATOR_H

#include <iostream>
#include "list.h"

template<class T>
class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    Node<T> *ptr = nullptr;
    list<T> *buck = nullptr;
    list<T> *map_begin = nullptr;
    list<T> *map_end = nullptr;

public:
    iterator(Node<T> *ptr_m, list<T> *buck_m, list<T> *map_begin_m,
             list<T> *map_end_m)
            : ptr(ptr_m), buck(buck_m),
              map_begin(map_begin_m), map_end(map_end_m) {}


    iterator<T> &operator++() {
        if (ptr == nullptr) {
            return *this;
        }
        if (ptr->next || buck == map_end - 1) {
            ptr = ptr->next.get();
        } else {
            buck += 1;
            while (buck->empty() && (buck != map_end - 1)) {
                buck += 1;
            }
            ptr = buck->begin().get();
        }
        return *this;
    }

    iterator<T> operator++(int) {
        if (ptr == nullptr) {
            return *this;
        }
        iterator<T> it1(*this);
        if (ptr->next || buck == map_end - 1) {
            ptr = ptr->next.get();
        } else {
            ++buck;
            while (buck->empty() && (buck != map_end - 1)) {
                ++buck;
            }
            ptr = buck->begin().get();
        }
        return it1;
    }

    iterator<T> &operator--() {
        if (ptr == nullptr) {
            return *this;
        }
        if (ptr->prev != nullptr) {
            ptr = ptr->prev.get();
        } else {
            if (buck != map_begin) {
                --buck;
                while (buck->empty() && (buck != map_begin)) {
                    --buck;
                }
                ptr = (buck->begin() + (buck->size() - 1)).get();
            }
        }
        return *this;
    }

    iterator<T> operator--(int) {
        iterator<Node<T>> it1(*this);
        if (ptr == nullptr) {
            return *this;
        }
        if (ptr->prev != nullptr) {
            ptr = ptr->prev.get();
        } else {
            if (buck != map_begin) {
                --buck;
                while (buck->empty() && (buck != map_begin)) {
                    --buck;
                }
                ptr = (buck->begin() + (buck->size() - 1)).get();
            }
        }
        return *it1;
    }

    iterator<T> &operator+=(size_t value) {
        for (size_t i = 0; i < value; ++i) {
            ++(*this);
        }
        return *this;
    }

    iterator<T> &operator-=(size_t value) {
        for (size_t i = 0; i < value; ++i) {
            --(*this);
        }
        return *this;
    }

    Node<T> *get() const { return ptr; }

    T &operator*() { return ptr->val; }

    const T &operator*() const { return ptr->val; }

    T *operator->() { return &ptr->val; }

    bool operator==(const iterator &oth) { return oth.ptr == ptr; }

    list<T> *get_buck() { return buck; }

    template<class Y>
    friend size_t operator-(iterator<Y> it_big, iterator<Y> it_small);
};

template<class T>
size_t operator-(iterator<T> it_big, iterator<T> it_small) {
    iterator<T> it_big_copy(it_big);
    size_t ans(0);
    while (it_big_copy != it_small) {
        if (it_big_copy == it_big_copy.buck->begin()) {
            throw std::logic_error("Invalid usage of iterator::operator- exception.");
        }
        ++ans;
        --it_big_copy;
    }
    return ans;
}

template<class T>
iterator<T> operator+(iterator<T> it, size_t value) {
    it += value;
    return it;
}

template<class T>
iterator<T> operator-(iterator<T> it, size_t value) {
    it -= value;
    return it;
}

template<class T>
bool operator!=(iterator<T> it1, const iterator<T> &it2) {
    return !(it1 == it2);
}
