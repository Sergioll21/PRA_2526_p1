#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

private:
    Node<T>* first;
    int n;

    void check_insert_pos(int pos) const {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("pos fuera de rango en insert");
        }
    }

    void check_access_pos(int pos) const {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("pos fuera de rango");
        }
    }

    Node<T>* node_at(int pos) const {
        // precondición: pos válido [0, n-1]
        Node<T>* cur = first;
        for (int i = 0; i < pos; ++i) {
            cur = cur->next;
        }
        return cur;
    }

public:
    // Constructor
    ListLinked() : first(nullptr), n(0) {}

    // Destructor (según la estrategia indicada)
    ~ListLinked() override {
        while (first != nullptr) {
            Node<T>* aux = first->next; // 1) aux = first->next
            delete first;               // 2) liberar first
            first = aux;                // 3) first = aux
        }
        n = 0;
    }

    // Métodos de la interfaz List<T>
    void insert(int pos, T e) override {
        check_insert_pos(pos);

        if (pos == 0) {
            first = new Node<T>(e, first);
            ++n;
            return;
        }

        Node<T>* prev = node_at(pos - 1);
        prev->next = new Node<T>(e, prev->next);
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

        if (pos == 0) {
            Node<T>* victim = first;
            T value = victim->data;
            first = first->next;
            delete victim;
            --n;
            return value;
        }

        Node<T>* prev = node_at(pos - 1);
        Node<T>* victim = prev->next;
        T value = victim->data;

        prev->next = victim->next;
        delete victim;
        --n;

        return value;
    }

    T get(int pos) override {
        check_access_pos(pos);
        return node_at(pos)->data;
    }

    int search(T e) override {
        Node<T>* cur = first;
        int idx = 0;
        while (cur != nullptr) {
            if (cur->data == e) return idx;
            cur = cur->next;
            ++idx;
        }
        return -1;
    }

    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }

    // operator[]
    T operator[](int pos) {
        check_access_pos(pos);
        return node_at(pos)->data;
    }

    // operator<<
    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
        out << "[";
        Node<T>* cur = list.first;
        while (cur != nullptr) {
            out << cur->data;
            if (cur->next != nullptr) out << ", ";
            cur = cur->next;
        }
        out << "]";
        return out;
    }
};

#endif

