
#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <iostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T> {
private:
    T* arr;
    int max;  // Capacidad del array
    int n;    // Numero de elementos
    static const int MINSIZE = 10;

    void resize(int new_size);

public:
    ListArray();
    ~ListArray() override;

    void insert(int pos, T e) override;
    void append(T e) override;
    void prepend(T e) override;
    T remove(int pos) override;
    T get(int pos) override;
    int search(T e) override;
    bool empty() override;
    int size() override;

    T operator[](int pos);

    friend std::ostream& operator<<(
        std::ostream& out, const ListArray<T>& list
    ) {
        for (int i = 0; i < list.n; i++) {
            if (i > 0) {
                out << " ";
            }
            out << list.arr[i];
        }
        return out;
    }
};

// Constructor
template <typename T>
ListArray<T>::ListArray() {
    max = MINSIZE;
    n = 0;
    arr = new T[max];
}

// Destructor
template <typename T>
ListArray<T>::~ListArray() {
    delete[] arr;
}

// Redimensionar el array
template <typename T>
void ListArray<T>::resize(int new_size) {
    if (new_size < MINSIZE) {
        new_size = MINSIZE;
    }

    T* new_arr = new T[new_size];

    for (int i = 0; i < n; i++) {
        new_arr[i] = arr[i];
    }

    delete[] arr;
    arr = new_arr;
    max = new_size;
}

// Insertar en una posicion
template <typename T>
void ListArray<T>::insert(int pos, T e) {
    if (pos < 0 || pos > n) {
        throw std::out_of_range("Posicion invalida");
    }

    if (n == max) {
        resize(max * 2);
    }

    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = e;
    n++;
}

// Insertar al final
template <typename T>
void ListArray<T>::append(T e) {
    insert(n, e);
}

// Insertar al principio
template <typename T>
void ListArray<T>::prepend(T e) {
    insert(0, e);
}

// Eliminar y devolver un elemento
template <typename T>
T ListArray<T>::remove(int pos) {
    if (pos < 0 || pos >= n) {
        throw std::out_of_range("Posicion invalida");
    }

    T value = arr[pos];

    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }

    n--;

    // Reducir capacidad si esta demasiado vacio
    if (max > MINSIZE && n <= max / 4) {
        resize(max / 2);
    }

    return value;
}

// Obtener un elemento
template <typename T>
T ListArray<T>::get(int pos) {
    if (pos < 0 || pos >= n) {
        throw std::out_of_range("Posicion invalida");
    }

    return arr[pos];
}

// Sobrecarga del operador []
template <typename T>
T ListArray<T>::operator[](int pos) {
    return get(pos);
}

// Buscar un elemento
template <typename T>
int ListArray<T>::search(T e) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == e) {
            return i;
        }
    }

    return -1;
}

// Comprobar si esta vacia
template <typename T>
bool ListArray<T>::empty() {
    return n == 0;
}

// Numero de elementos
template <typename T>
int ListArray<T>::size() {
    return n;
}

#endif

