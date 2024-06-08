#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include "NodoArbol.h"
#include "Lista.h"

template <class T>
class arbol {
private:
    NodoArbol<T>* raiz;
    int nbits;

    void ArbolBusqAlf(NodoArbol<T>* x, NodoArbol<T>*& nuevo);
    void ArbolBusqRep(NodoArbol<T>* x, NodoArbol<T>*& nuevo);
    void ird(NodoArbol<T>* aux, std::ostream& out);
    void GenLista_ird(Lista<T>* laux, NodoArbol<T>* aux);
    void mhrep(NodoArbol<T>* aux, std::ostream& out);

public:
    arbol();
    void setMaxBit(int b);
    int getMaxBit();
    void CreaArbolBusAlf(NodoArbol<T>* x);
    void CreaArbolBusRep(NodoArbol<T>* x);
    void IRD(std::ostream& out);
    void GenLista_IRD(Lista<T>* l);
    void MostrarHojasRep(std::ostream& out);
    NodoLista<T>* atPos(int pos);
};

template <class T>
arbol<T>::arbol() : raiz(NULL), nbits(0) {}

template <class T>
void arbol<T>::setMaxBit(int b) {
    nbits = b;
}

template <class T>
int arbol<T>::getMaxBit() {
    return nbits;
}

template <class T>
void arbol<T>::CreaArbolBusAlf(NodoArbol<T>* x) {
    ArbolBusqAlf(x, raiz);
}

// Inserta nodos en un arbol binario siguiendo un orden alfabetico y para que al recorrer el arbol de la forma
// IRD muestre todos los elementos ordenados alfabeticamente
template <class T>
void arbol<T>::ArbolBusqAlf(NodoArbol<T>* x, NodoArbol<T>*& nuevo) {
    if (nuevo == NULL) {
        nuevo = x;
        nuevo->der = nuevo->izq = NULL;
    }
    else if (x->get_nodoDato()->get_dato() > nuevo->get_nodoDato()->get_dato()) {
        ArbolBusqAlf(x, nuevo->der);
    }
    else if (x->get_nodoDato()->get_dato() < nuevo->get_nodoDato()->get_dato()) {
        ArbolBusqAlf(x, nuevo->izq);
    }
}

template <class T>
void arbol<T>::CreaArbolBusRep(NodoArbol<T>* x) {
    this->setMaxBit(x->get_nodoLista()->get_binary().size() - 1);
    ArbolBusqRep(x, raiz);
}

// Inserta nodos en un arbol binario basado en la secuencia de instruccion almacenada en NodoDato
// Cuando la instruccion tiene un MSB=0, el metodo sigue por la rama izquierda, si no va a la derecha
template <class T>
void arbol<T>::ArbolBusqRep(NodoArbol<T>* x, NodoArbol<T>*& nuevo) {
    if (nuevo == NULL) {
        nuevo = new NodoArbol<T>;
        nuevo->der = nuevo->izq = NULL;
    }
    // Obtiene el MSB de la instruccion
    char actualInstruction = x->get_nodoLista()->get_nodoDato()->instruction.at(0);
    // Borra el MSB de la instruccion (para no tener problemas en las recursiones que siguen)
    x->get_nodoLista()->get_nodoDato()->instruction.erase(0, 1);
    if (actualInstruction == '0') {
        // Si la instruccion esta vacia, quiere decir que tengo que insertar el nodo que apunta a la lista
        if (x->get_nodoLista()->get_nodoDato()->instruction.empty()) {
            nuevo->izq = x;
        } else {
            ArbolBusqRep(x, nuevo->izq);
        }
    } else {
        if (x->get_nodoLista()->get_nodoDato()->instruction.empty()) {
            nuevo->der = x;
        } else {
            ArbolBusqRep(x, nuevo->der);
        }
    }
}

template <class T>
void arbol<T>::ird(NodoArbol<T>* aux, std::ostream& out) {
    if (aux != NULL) {
        ird(aux->izq, out);
        out << "Palabra: " << aux->get_dato() << std::endl;
        ird(aux->der, out);
    }
}

// Se genera una lista nueva haciendo un recorrido ird del arbol
template <class T>
void arbol<T>::GenLista_ird(Lista<T>* laux, NodoArbol<T>* aux) {
    if (aux != NULL) {
        GenLista_ird(laux, aux->izq);
        laux->add(aux->get_dato());
        laux->cabezaNodo()->get_nodoDato()->set_reps(aux->get_nodoDato()->get_reps());
        GenLista_ird(laux, aux->der);
    }
}

template <class T>
void arbol<T>::mhrep(NodoArbol<T>* aux, std::ostream& out) {
    if (aux != NULL) {
        mhrep(aux->izq, out);
        if (aux->izq == NULL && aux->der == NULL)
            out << aux->get_datoLista() << " || Binary Code: " << aux->get_nodoLista()->get_binary() << std::endl;
        mhrep(aux->der, out);
    }
}

// IRD significa "In-Order, Root, Descendant"
// En este  caso, se recorre el subarbol izquierdo>se visita el nodo raiz>se recorre el subarbol derecho
template <class T>
void arbol<T>::IRD(std::ostream& out) {
    ird(raiz, out);
}

template <class T>
void arbol<T>::GenLista_IRD(Lista<T>* l) {
    GenLista_ird(l, raiz);
}

template <class T>
void arbol<T>::MostrarHojasRep(std::ostream& out) {
    mhrep(raiz, out);
}

// Este metodo encuentra un nodo en la estructura de arbol posicional convirtiendo la posicion ingresada en una secuencia de bits y utilizando esa secuencia para navegar el arbol
template <class T>
NodoLista<T>* arbol<T>::atPos(int pos) {
    int bits = this->nbits;
    int m1 = pos - 1;
    std::string bitset;
    // Convierto m1 en binario
    for (int i = 0; i <= bits; i++) {
        while (m1 != 0) {
            bitset = (m1 % 2 == 0 ? "0" : "1") + bitset;
            m1 /= 2;
            i++;
        }
        if (i <= bits) {
            bitset = "0" + bitset;
        }
    }
    // Empiezo a recorrer el arbol desde la raiz
    NodoArbol<T>* temp = (bitset.at(0) == '0') ? this->raiz->izq : this->raiz->der;
    // Recorro el arbol hasta llegar al penultimo bit del bitset que se armo antes
    for (int i = 1; i < bits; i++) {
        temp = (bitset.at(i) == '0') ? temp->izq : temp->der;
    }
    // Como ya es el ultimo bit, lo que siga va a ser el nodoLista que se busca obtener
    return (bitset.at(bits) == '0') ? temp->izq->get_nodoLista() : temp->der->get_nodoLista();
}

#endif // ARBOL_H
