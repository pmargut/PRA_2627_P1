#ifndef LIST_LINKED_H
#define LIST_LINKED_H

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
        // Constructor sin argumentos
        ListLinked() : first(nullptr), n(0) {}

        // Destructor que libera la memoria dinámica de los nodos
        ~ListLinked() {
            while (first != nullptr) {
                Node<T>* aux = first->next;
                delete first;
                first = aux;
            }
        }

        // Sobrecarga del operador []
        T operator[](int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }

            Node<T>* curr = first;
            for (int i = 0; i < pos; ++i) {
                curr = curr->next;
            }
            return curr->data;
        }

        // Métodos heredados de la interfaz List<T>
        void insert(int pos, T e) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posición fuera de rango");
            }

            if (pos == 0) {
                first = new Node<T>(e, first);
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; ++i) {
                    prev = prev->next;
                }
                prev->next = new Node<T>(e, prev->next);
            }
            n++;
        }

        void append(T e) override {
            insert(n, e);
        }

        void prepend(T e) override {
            insert(0, e);
        }

        T remove(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }

            Node<T>* toDelete;
            if (pos == 0) {
                toDelete = first;
                first = first->next;
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; ++i) {
                    prev = prev->next;
                }
                toDelete = prev->next;
                prev->next = toDelete->next;
            }

            T data = toDelete->data;
            delete toDelete;
            n--;
            return data;
        }

        T get(int pos) override {
            return (*this)[pos];
        }

        int search(T e) override {
            Node<T>* curr = first;
            int pos = 0;
            while (curr != nullptr) {
                if (curr->data == e) {
                    return pos;
                }
                curr = curr->next;
                pos++;
            }
            return -1;
        }

        bool empty() override {
            return n == 0;
        }

        int size() override {
            return n;
        }

        // Sobrecarga del operador <<
        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const ListLinked<U>& list);
};

// Implementación de la sobrecarga del operador <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
    out << "[";
    Node<T>* curr = list.first;
    while (curr != nullptr) {
        out << curr->data;
        if (curr->next != nullptr) {
            out << ", ";
        }
        curr = curr->next;
    }
    out << "]";
    return out;
}

#endif // LIST_LINKED_H
