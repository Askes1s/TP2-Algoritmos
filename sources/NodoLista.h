#ifndef NODOLISTA_H
#define NODOLISTA_H

#include <string>
#include "NodoDato.h"

// Esta clase es utilizada para listas enlazadas, contiene un NodoDato y un puntero al siguiente NodoLista

template <class T>
class NodoLista {
private:
    NodoDato<T>* nodoDato;
    NodoLista<T>* next;

public:
    NodoLista<T>* izq;
    NodoLista<T>* der;

    NodoLista();
    NodoLista(T a);
    void set_nodoDato(NodoDato<T>* a);
    void set_next(NodoLista* n);
    void repetido();
    T get_dato();
    NodoDato<T>* get_nodoDato();
    int get_reps();
    std::string get_binary();
    NodoLista<T>* get_next();
    bool es_vacio();
};

template <class T>
NodoLista<T>::NodoLista() : nodoDato(NULL), next(NULL), izq(NULL), der(NULL) {}

template <class T>
NodoLista<T>::NodoLista(T a) : nodoDato(new NodoDato<T>(a)), next(NULL), izq(NULL), der(NULL) {}

template <class T>
void NodoLista<T>::set_nodoDato(NodoDato<T>* a) {
    nodoDato = a;
}

template <class T>
void NodoLista<T>::set_next(NodoLista* n) {
    next = n;
}

template <class T>
void NodoLista<T>::repetido() {
    if (nodoDato != NULL) {
        nodoDato->repetido();
    }
}

template <class T>
T NodoLista<T>::get_dato() {
    if (nodoDato != NULL) {
        return nodoDato->get_dato();
    }
    return T();
}

template <class T>
NodoDato<T>* NodoLista<T>::get_nodoDato() {
    return nodoDato;
}

template <class T>
int NodoLista<T>::get_reps() {
    if (nodoDato == NULL) {
        return 0;
    }
    return nodoDato->get_reps();
}

template <class T>
std::string NodoLista<T>::get_binary() {
    if (nodoDato == NULL) {
        return "No hay nodo asignado";
    }
    if (nodoDato->get_binary().empty()) {
        return "No hay binario asignado";
    } else {
        return nodoDato->get_binary();
    }
}

template <class T>
NodoLista<T>* NodoLista<T>::get_next() {
    return next;
}

template <class T>
bool NodoLista<T>::es_vacio() {
    return next == NULL;
}

#endif // NODOLISTA_H
