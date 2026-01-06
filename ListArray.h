#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T> 
class ListArray : public List<T> {

private:
    T* arr;
    int max;
    int n;
    static const int MINSIZE = 2;

    void resize(int new_size) {
        if (new_size < MINSIZE) new_size = MINSIZE;

        T* new_arr = new T[new_size];

        int limit = (n < new_size) ? n : new_size;
        for (int i = 0; i < limit; ++i) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
        max = new_size;

        if (n > max) n = max;
    }

    void check_insert_pos(int pos) const {
        if (pos < 0 || pos > n)
            throw std::out_of_range("pos fuera de rango en insert");
    }

    void check_access_pos(int pos) const {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("pos fuera de rango");
    }

public:
    ListArray() : arr(new T[MINSIZE]), max(MINSIZE), n(0) {}

    ~ListArray() override {
        delete[] arr;
    }

    void insert(int pos, T e) override {
        check_insert_pos(pos);

        if (n == max)
            resize(max * 2);

        for (int i = n; i > pos; --i)
            arr[i] = arr[i - 1];

        arr[pos] = e;
        ++n;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        check_access_pos(pos);

        T removed = arr[pos];

        for (int i = pos; i < n - 1; ++i)
            arr[i] = arr[i + 1];

        --n;

        if (max > MINSIZE && n <= max / 4) {
            int new_cap = max / 2;
            if (new_cap < MINSIZE) new_cap = MINSIZE;
            resize(new_cap);
        }

        return removed;
    }

    T get(int pos) override {
        check_access_pos(pos);
        return arr[pos];
    }

    int search(T e) override {
        for (int i = 0; i < n; ++i) {
            if (arr[i] == e)
                return i;
        }
        return -1;
    }

    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }

    T operator[](int pos) {
        check_access_pos(pos);
        return arr[pos];
    }

    friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list) {
        out << "[";
        for (int i = 0; i < list.n; ++i) {
            out << list.arr[i];
            if (i != list.n - 1) out << ", ";
        }
        out << "]";
        return out;
    }
};

#endif

