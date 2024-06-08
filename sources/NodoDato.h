#ifndef NODODATO_H
#define NODODATO_H

#include <string>

// Esta clase almacena los datos en si y datos adicionales como las repeticiones y el codigo binario
// Se utiliza para las listas

template <class T>
class NodoDato {
private:
    T dato;
    int repeticiones;
    std::string binary;
public:
    std::string instruction;
    
    NodoDato(T a);
    void repetido();
    T get_dato() const;
    int get_reps() const;
    void set_reps(int r);
    std::string get_binary() const;
    void set_binary(const std::string& a);
};

template <class T>
NodoDato<T>::NodoDato(T a) : dato(a), repeticiones(1) {}

template <class T>
void NodoDato<T>::repetido() {
    repeticiones++;
}

template <class T>
T NodoDato<T>::get_dato() const {
    return dato;
}

template <class T>
int NodoDato<T>::get_reps() const {
    return repeticiones;
}

template <class T>
void NodoDato<T>::set_reps(int r) {
    repeticiones = r;
}

template <class T>
std::string NodoDato<T>::get_binary() const {
    return binary;
}

template <class T>
void NodoDato<T>::set_binary(const std::string& a) {
    binary = a;
    instruction = a;
}

#endif // NODODATO_H
