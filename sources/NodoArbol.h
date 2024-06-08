#ifndef NODOARBOL_H
#define NODOARBOL_H

#include "NodoDato.h"
#include "NodoLista.h"

// Esta clase es utilizada para arboles binarios y puede contener un NodoDato o un NodoLista, y tiene punteros a hijos izquierdo y derecho
// Los Nodos Arbol que contienen Nodos Dato son para el arbol alfabetico, y los Nodos Arbol que contienen Nodos Lista son para el arbol posicional

template <class T>
class NodoArbol {
private:
    NodoDato<T>* nodoDato;
    NodoLista<T>* nodoLista;

public:
    NodoArbol<T>* izq;
    NodoArbol<T>* der;

    NodoArbol();
    NodoArbol(NodoDato<T>* a);
    NodoArbol(NodoLista<T>* a);
    
    NodoDato<T>* get_nodoDato() const;
    void set_nodoDato(NodoDato<T>* a);
    
    T get_dato() const;
    int get_reps() const;
    
    NodoLista<T>* get_nodoLista() const;
    T get_datoLista() const;
};

template <class T>
NodoArbol<T>::NodoArbol() : nodoDato(NULL), nodoLista(NULL), izq(NULL), der(NULL) {}

template <class T>
NodoArbol<T>::NodoArbol(NodoDato<T>* a) : nodoDato(a), nodoLista(NULL), izq(NULL), der(NULL) {}

template <class T>
NodoArbol<T>::NodoArbol(NodoLista<T>* a) : nodoDato(NULL), nodoLista(a), izq(NULL), der(NULL) {}

template <class T>
NodoDato<T>* NodoArbol<T>::get_nodoDato() const {
    return nodoDato;
}

template <class T>
void NodoArbol<T>::set_nodoDato(NodoDato<T>* a) {
    nodoDato = a;
}

template <class T>
T NodoArbol<T>::get_dato() const {
    if (nodoDato != NULL) {
        return nodoDato->get_dato();
    }
    return T();
}

template <class T>
int NodoArbol<T>::get_reps() const {
    if (nodoDato == NULL) {
        return 0;
    }
    return nodoDato->get_reps();
}

template <class T>
NodoLista<T>* NodoArbol<T>::get_nodoLista() const {
    return nodoLista;
}

template <class T>
T NodoArbol<T>::get_datoLista() const {
    if (nodoLista != NULL) {
        return nodoLista->get_dato();
    }
    return T();
}

#endif // NODOARBOL_H
