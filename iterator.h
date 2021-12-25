// Copyright 2021 Bogdan Shumilishskiy bshumilishsky@mail.ru

#ifndef TEMPLATE_ITERATOR_H
#define TEMPLATE_ITERATOR_H

#endif  // TEMPLATE_ITERATOR_H

#include <iostream>
#include "list.h"

template<class T>
class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    std::shared_ptr<Node<T>> ptr = nullptr;
    std::shared_ptr<list<T>> buck = nullptr;
    std::shared_ptr<list<T>> map_begin = nullptr;
    std::shared_ptr<list<T>> map_end = nullptr;

public:
//    iterator(Node<T> *ptr_m, list<T> *buck_m, list<T> *map_begin_m,
//             list<T> *map_end_m)
//            : ptr(ptr_m), buck(buck_m),
//              map_begin(map_begin_m), map_end(map_end_m) {}
    iterator(const std::shared_ptr<Node<T>> &ptr_m, const std::shared_ptr<list<T>> &buck_m,
             const std::shared_ptr<list<T>> &map_begin_m,
             const std::shared_ptr<list<T>> &map_end_m) : ptr(ptr_m), buck(buck_m), map_begin(map_begin_m),
                                                          map_end(map_end_m) {}

    iterator(const std::shared_ptr<list<T>> &list_ptr, const std::shared_ptr<list<T>> &map_begin_m,
             const std::shared_ptr<list<T>> &map_end_m) : ptr(list_ptr->begin().get()), buck(list_ptr),
                                                          map_begin(map_begin_m), map_end(map_begin_m) {}

    iterator<T> &operator++() {
        if (ptr.get() == nullptr) {
            return *this;
        }
        if (ptr->next || buck.get() == map_end.get() - 1) {
            ptr = ptr->next;
        } else {
            buck.reset(buck.get() + 1);
            while (buck->empty() && (buck.get() != map_end.get() - 1)) {
                buck.reset(buck.get() + 1);
            }
            ptr = std::shared_ptr<Node<T>>(buck->begin().get());
        }
        return *this;
    }

    iterator<T> operator++(int) {
        if (ptr.get() == nullptr) {
            return std::make_shared<Node<T>>(nullptr);
        }
        iterator<T> it1(*this);
        if (ptr->next || buck == map_end - 1) {
            ptr = ptr->next;
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
        if (ptr.get() == nullptr) {
            return std::make_shared<Node<T>>(nullptr);
        }
        if (ptr->prev != nullptr) {
            ptr = ptr->prev;
        } else {
            if (buck.get() != map_begin) {
                --buck;
                while (buck->empty() && (buck.get() != map_begin.get())) {
                    --buck;
                }
                ptr = std::make_shared<Node<T>>((buck->begin() + (buck->size() - 1)).get());
            }
        }
        return *this;
    }

    iterator<T> operator--(int) {
        iterator<Node<T>> it1(*this);
        if (ptr.get() == nullptr) {
            return std::make_shared<Node<T>>(nullptr);
        }
        if (ptr->prev != nullptr) {
            ptr = ptr->prev;
        } else {
            if (buck.get() != map_begin) {
                --buck;
                while (buck->empty() && (buck.get() != map_begin.get())) {
                    --buck;
                }
                ptr = std::make_shared<Node<T>>((buck->begin() + (buck->size() - 1)).get());
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

    Node<T> *get() const { return ptr.get(); }

    T &operator*() { return ptr->val; }

    const T &operator*() const { return ptr->val; }

    T *operator->() { return &ptr->val; }

    bool operator==(const iterator &oth) { return oth.ptr.get() == ptr.get(); }

    list<T> *get_buck() { return buck.get(); }

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
