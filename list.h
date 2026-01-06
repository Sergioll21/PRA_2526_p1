#ifndef LIST_H
#define LIST_H

#include <stdexcept>

template <typename T>
class List {
public:
    virtual ~List() = default;

    // Inserta el elemento e en la posición pos (pos en [0, size()])
    virtual void insert(int pos, T e) = 0;

    // Inserta el elemento al final de la lista
    virtual void append(T e) = 0;

    // Inserta el elemento al principio de la lista
    virtual void prepend(T e) = 0;

    // Elimina y devuelve el elemento en la posición pos (pos en [0, size()-1])
    virtual T remove(int pos) = 0;

    // Devuelve el elemento en la posición pos (pos en [0, size()-1])
    virtual T get(int pos) = 0;

    // Devuelve la posición de la primera ocurrencia de e o -1 si no se encuentra
    virtual int search(T e) = 0;

    // Indica si la lista está vacía
    virtual bool empty() = 0;

    // Devuelve el número de elementos de la lista
    virtual int size() = 0;
};

#endif

