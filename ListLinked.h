
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

public:
    // Constructor
    ListLinked() : first(nullptr), n(0) {
    }

    // Destructor
    ~ListLinked() override {
        Node<T>* current = first;

        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }

        first = nullptr;
        n = 0;
    }

    // Insertar en una posicion
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Posicion invalida");
        }

        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* current = first;

            for (int i = 0; i < pos - 1; i++) {
                current = current->next;
            }

            current->next = new Node<T>(e, current->next);
        }

        n++;
    }

    // Insertar al final
    void append(T e) override {
        insert(n, e);
    }

    // Insertar al principio
    void prepend(T e) override {
        insert(0, e);
    }

    // Eliminar y devolver un elemento
    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posicion invalida");
        }

        Node<T>* temp;
        T value;

        if (pos == 0) {
            temp = first;
            first = first->next;
        } else {
            Node<T>* current = first;

            for (int i = 0; i < pos - 1; i++) {
                current = current->next;
            }

            temp = current->next;
            current->next = temp->next;
        }

        value = temp->data;
        delete temp;
        n--;

        return value;
    }

    // Obtener un elemento
    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posicion invalida");
        }

        Node<T>* current = first;

        for (int i = 0; i < pos; i++) {
            current = current->next;
        }

        return current->data;
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        return get(pos);
    }

    // Buscar la primera ocurrencia
    int search(T e) override {
        Node<T>* current = first;
        int pos = 0;

        while (current != nullptr) {
            if (current->data == e) {
                return pos;
            }

            current = current->next;
            pos++;
        }

        return -1;
    }

    // Comprobar si esta vacia
    bool empty() override {
        return n == 0;
    }

    // Devolver el numero de elementos
    int size() override {
        return n;
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(
        std::ostream& out, const ListLinked<T>& list
    ) {
        Node<T>* current = list.first;

        while (current != nullptr) {
            out << current->data;

            if (current->next != nullptr) {
                out << " ";
            }

            current = current->next;
        }

        return out;
    }
};

#endif

