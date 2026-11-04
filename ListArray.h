#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T>{
	
	private:
	T* arr;             // Puntero al inicio del array dinámico
        int max;            // Tamaño actual del array (capacidad máxima)
        int n;              // Número actual de elementos en la lista
        static const int MINSIZE = 2; // Tamaño mínimo del array

        // Método privado para redimensionar el array
        void resize(int new_size) {
            T* new_arr = new T[new_size];
            for (int i = 0; i < n; ++i) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
            max = new_size;
		}
	public:

	ListArray() {
            max = MINSIZE;
            n = 0;
            arr = new T[max];
        }

        // Destructor virtual sobrescrito
        ~ListArray() override {
            delete[] arr;
        }

        // Sobrecarga del operador []
        T operator[](int pos) {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posicion fuera de rango en operator[]");
            }
            return arr[pos];
        }

        // --- Métodos virtuales puros heredados de List<T> ---

        void insert(int pos, T e) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posicion fuera de rango en insert()");
            }
            if (n == max) {
                resize(max * 2);
            }
            for (int i = n; i > pos; --i) {
                arr[i] = arr[i - 1];
            }
            arr[pos] = e;
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
                throw std::out_of_range("Posicion fuera de rango en remove()");
            }
            T element = arr[pos];
            for (int i = pos; i < n - 1; ++i) {
                arr[i] = arr[i + 1];
            }
            n--;

            // Reducción opcional de capacidad si hay mucho espacio libre
            if (max > MINSIZE && n <= max / 4) {
                int new_size = max / 2;
                if (new_size < MINSIZE) new_size = MINSIZE;
                resize(new_size);
            }

            return element;
        }

        T get(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posicion fuera de rango en get()");
            }
            return arr[pos];
        }

        int search(T e) override {
            for (int i = 0; i < n; ++i) {
                if (arr[i] == e) {
                    return i;
                }
            }
            return -1;
        }

        bool empty() override {
            return n == 0;
        }

        int size() override {
            return n;
        }

        // Sobrecarga global del operador << como función amiga (friend)
        friend std::ostream& operator<<(std::ostream &out, ListArray<T> &list) {
            out << "[";
            for (int i = 0; i < list.n; ++i) {
                out << list.arr[i];
                if (i < list.n - 1) {
                    out << ", ";
                }
            }
            out << "]";
            return out;
        }
};
