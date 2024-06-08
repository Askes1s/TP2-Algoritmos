#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "NodoLista.h"

template <class T>
class Lista {
private:
    NodoLista<T>* czo;

public:
    Lista();
    Lista(NodoLista<T>* n);

    void add(T d); // Agrega nodo a la lista (EL ULTIMO AÑADIDO ES LA CABEZA)
    bool esvacia(void);
    T cabeza(void); // Retorna el dato del primer nodo de la lista (EL ULTIMO ELEMENTO AÑADIDO A LA LISTA)
    NodoLista<T>* cabezaNodo(); // Retorna puntero al ultimo elemento añadido
    Lista* resto(void); // Retorna el puntero al "resto" de la lista
                        // Resto: lo que queda de la lista sin la cabeza
    void impreRep(std::ostream& out);
    void impreAlf(std::ostream& out);
    int size();
    bool esta(T d); // Detecta si d esta en la lista
    T last(); // Retorna el dato del ultimo nodo (EL PRIMER ELEMENTO AÑADIDO A LA LISTA)
    NodoLista<T>* at(int n); // Devuelve el elemento n de la lista (Cuenta desde la cabeza en 0 hasta N-1 siendo N el tamaño de la lista)
};

template <class T>
Lista<T>::Lista() : czo(new NodoLista<T>()) {}

template <class T>
Lista<T>::Lista(NodoLista<T>* n) : czo(n) {}

template <class T>
void Lista<T>::add(T d) {
    NodoLista<T>* nuevo = new NodoLista<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}

template <class T>
bool Lista<T>::esvacia(void) {
    return czo->es_vacio();
}

template <class T>
T Lista<T>::cabeza(void) {
    if (this->esvacia()) {
        std::cout << "Error, Cabeza de lista vacia";
        return T();
    }
    return czo->get_dato();
}

template <class T>
NodoLista<T>* Lista<T>::cabezaNodo(void) {
    if (this->esvacia()) {
        std::cout << "Error, Cabeza de lista vacia";
        return nullptr;
    }
    return czo;
}

template <class T>
Lista<T>* Lista<T>::resto(void) {
    return new Lista(czo->get_next());
}

template <class T>
void Lista<T>::impreRep(std::ostream& out) {
    NodoLista<T>* aux = czo;
    while (aux->get_next() != NULL) {
        out << "Palabra: " << aux->get_dato() << " || Repeticiones: " << aux->get_reps() << " || Binary code: " << aux->get_binary() << std::endl;
        aux = aux->get_next();
    }
}

template <class T>
void Lista<T>::impreAlf(std::ostream& out) {
    NodoLista<T>* aux = czo;
    while (aux->get_next() != NULL) {
        out << "Palabra: " << aux->get_dato() << std::endl;
        aux = aux->get_next();
    }
}

template <class T>
int Lista<T>::size() {
    if (this->esvacia()) return 0;
    return 1 + this->resto()->size();
}

// Va recorriendo la lista recursivamente hasta que la cabeza sea el dato que se busca (si eso nunca sucede, devuelve false, sino devuelve true y aumenta las reps del dato)
template <class T>
bool Lista<T>::esta(T d) {
    if (this->esvacia()) return false;
    if (this->cabeza() == d) {
        czo->repetido();
        return true;
    }
    return this->resto()->esta(d);
}

template <class T>
T Lista<T>::last() {
    if (!this->esvacia()) {
        if (this->resto()->esvacia()) return this->cabeza();
        return this->resto()->last();
    }
    return T();
}

template <class T>
NodoLista<T>* Lista<T>::at(int n) {
    if (this->esvacia()) {
        return nullptr;
    }
    Lista<T>* listaux = this;
    NodoLista<T>* temp;
    for (int i = 0; i <= n; i++) {
        if (i == n) {
            temp = listaux->cabezaNodo();
        } else {
            listaux = listaux->resto();
        }
    }
    return temp;
}

#endif // LISTA_H
