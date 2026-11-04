#ifndef NODE_H
#define NODE_H

#include <ostream>

template <typename T>
class Node {
public:
    // Atributos públicos
    T data;
    Node<T>* next;

    // Constructor con valor por defecto para next
    Node(T data, Node<T>* next = nullptr) 
        : data(data), next(next) {}

    // Sobrecarga del operador << como función amiga genérica
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Node<U>& node);
};

// Implementación del operador <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>& node) {
    out << node.data;
    return out;
}

#endif // NODE_H
