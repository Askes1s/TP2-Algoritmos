#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include "NodoDato.h"
#include "NodoLista.h"
#include "NodoArbol.h"
#include "Lista.h"
#include "arbol.h"

using namespace std;

/*
! FUNCIONES
*/

// La función recibe una copia del puntero, por lo que puede modificar el objeto al que apunta el puntero, pero no puede cambiar 
// el puntero para que apunte a otro objeto.
// La función recibe una referencia al objeto original, lo que le permite modificar el objeto directamente. No puede hacer que 
// la referencia apunte a otro objeto (las referencias no pueden ser reasignadas).
template <class T> int identifyWords(Lista<T>* lista, arbol<T>& arbol) {
    // Abrimos el txt
    ifstream i_file("../docs/ejemplo.txt");

    // Se pudo abrir el archivo?
    if (!i_file.is_open()) {
        return 0;
    }

    // Leemos el contenido del archivo en una cadena
    wstring contenido_txt((istreambuf_iterator<char>(i_file)), istreambuf_iterator<char>());
    // Si el archivo está vacio, devuelve error
    if (contenido_txt.length()==0) {
        return -1;
    }

    int totalLetters = contenido_txt.length();
    int ctdr = 0;
    int wordLetters = 0;
    int totalWords = 0;
    string word;
    for (char c : contenido_txt) {
        ctdr++;
        // Armo las palabras analizando que tengan letras o numeros (excluye letras con acento o similares)
        if ((48<=int(c) && int(c)<=57) || (65<=int(c) && int(c)<=90) || (97<=int(c) && int(c)<=122)) {
            // Si es una mayuscula, pasa a minuscula
            if (65<=int(c) && int(c)<=90) {
                c = tolower(c);
            }
            word+=c;
            wordLetters++;
            // Para el caso en el que el archivo termina en una letra valida
            if (ctdr==totalLetters) {
                if (!lista->esta(word)) {
                    lista->add(word);
                    NodoArbol<T>* temp = new NodoArbol<T>(lista->cabezaNodo()->get_nodoDato());
                    arbol.CreaArbolBusAlf(temp);
                }
                totalWords++;
                word.clear();
                wordLetters=0;
            }
        }
        else {
            //Agrego la palabra a la lista
            if (!word.empty()) {
                if (!lista->esta(word)) {
                    lista->add(word);
                    NodoArbol<T>* temp = new NodoArbol<T>(lista->cabezaNodo()->get_nodoDato());
                    arbol.CreaArbolBusAlf(temp);
                }
                totalWords++;
                word.clear();
                wordLetters=0;
            }
            //Agrego el separador como palabra
            string s = string() + c;
            if (!lista->esta(s)) {
                lista->add(s);
                NodoArbol<T>* temp = new NodoArbol<T>(lista->cabezaNodo()->get_nodoDato());
                arbol.CreaArbolBusAlf(temp);
            }
        }
        //El metodo esta() fue modificado para que se encargue de aumentar el numero de repeticiones si corresponde
    }
    cout << "CANTIDAD DE PALABRAS (incluyendo repetidas): " << totalWords << endl;
    cout << "CANTIDAD DE PALABRAS DIFERENTES: " << lista->size() << endl;
    cout << "CANTIDAD DE PALABRAS REPETIDAS: " << totalWords-lista->size() << endl;
    i_file.close();
    return 1;
}

template <class T> void swapDatoNodosLista(NodoLista<T>* a, NodoLista<T>* b) {
    NodoDato<T>* temp = b->get_nodoDato();
    b->set_nodoDato(a->get_nodoDato());
    a->set_nodoDato(temp);
}

// n^2 en todos los casos
// En cada iteracion se busca al elemento mas pequeño de la parte no ordenada de la lista y se lo intercambia
// con el primer elemento de la parte no ordenada de la lista (pasando a estar dentro de la parte ordenada)
template <class T> int selDirReps(Lista<T>* aux) {
    int i,j,pos,men,m=0,c=0;
    //recorrer todos los elementos de la lista
    for(i=0;i<aux->size();i++){
        //valor inicial del menor
        men=aux->at(i)->get_nodoDato()->get_reps(); pos=i; m++;
        //buscar menor elemento
        for(j=i+1;j<aux->size();j++){
            c++;
            //el elemento j de la lista es menor que men?
            if(aux->at(j)->get_nodoDato()->get_reps()<men){
                //nuevo valor de men
                men=aux->at(j)->get_nodoDato()->get_reps(); m++;
                pos=j; //pos es la posicion del menor e i es la posicion del numero con el que comparo
            }
        }
        //swap el menor dato que se encontró en la ultima iteracion con el actual elemento de la lista
        swapDatoNodosLista(aux->at(pos),aux->at(i)); m++; m++;
    }
    return c;
}

// Intercambia los datos de los limites inferior y superior (que se van cerrando e intercambiando hasta llegar a la mitad de la lista)
template <class T> void rotarLista(Lista<T>* aux) {
    int size = aux->size();
    int low = 0;
    int high = size-1;
    if (size%2==0) {
        for (int i=size-1;i>=size/2;i--) {
            swapDatoNodosLista(aux->at(low),aux->at(high));
            low++;
            high--;
        }
    } else {
        for (int i=size-1;i>(size-1)/2;i--) {
            swapDatoNodosLista(aux->at(low),aux->at(high));
            low++;
            high--;
        }
    }
}

// Configura el codigo binario de cada dato dentro de la lista (que debe ser la lista ordenada por reps)
template <class T> void setBinaries(Lista<T>* aux) {
    int size = aux->size();
    int nbits = 0;
    // Establece que tan largo tiene que ser el codigo binario
    while (int(pow(2,nbits+1))<size) {
        nbits++;
    }
    // Recorre todos los elementos de la lista
    for (int i=0;i<size;i++) {
        string r;
        int temp = i;
        for (int j=0;j<=nbits;j++) {
            // Toma la posicion de la lista, la va diviendo en 2 y cada vez que hace eso agrega un MSB al codigo
            while(temp!=0) {
                r=(temp%2==0 ?"0":"1")+r;
                temp/=2;
                j++;
            }
            // Por si en el while no se cubrieron todos los bits hasta llegar al largo necesario
            if (j<=nbits) {
                r="0"+r;
            }
        }
        aux->at(i)->get_nodoDato()->set_binary(r);
    }
}

template <class T> void GenArbolDeAcceso(Lista<T>* auxl, arbol<T>& arbol) {
    for (int i=0;i<auxl->size();i++) {
        NodoArbol<T>* temp = new NodoArbol<T>(auxl->at(i));
        arbol.CreaArbolBusRep(temp);
    }
}

// n/log(n) en promedio y en el mejor caso, n^2 en el peor caso
// El peor caso seria cuando la seleccion del pivote es siempre el elemento mas pequeño o mas grande de la sublista actual, lo que lleva a que
// una de las particiones tenga n-1 elementos y la otra 0 elementos. Ej.: elijo el primer elemento como pivote y la lista ya esta ordenada en orden ascendente
// Se selecciona un elemento como pivote, que se puede elegir de diferentes formas, en este caso se elije el ultimo elemento, y los elementos de la lista se
// reorganizan de modo que todos los elementos menores que el pivote se colocan antes de el y que todos los elementos mayores se colocan despues, por lo que al final
// de la iteracion, el pivote queda en su posicion final
// Es mas eficiente que SD porque divide al problema en subpartes y resuelve cada subparte de forma recursiva (reduce el numero de comparaciones)
template <class T> int ordenaQS(arbol<T>& a, int primero, int ultimo){ 
    int i,j;
    string pivot;
    int cc,cm=0;
        if(ultimo>primero){
            // Fijo al pivote como el ultimo dato de la lista
            pivot=a.atPos(ultimo)->get_nodoDato()->get_dato();cm++;
            i=primero-1; j=ultimo;
            for(;;) {
                // aumenta i hasta encontrar un dato mayor al pivote
                while(a.atPos(++i)->get_nodoDato()->get_dato()<pivot)cc++;
                // reduce j hasta encontrar un dato menor al pivote
                while(a.atPos(--j)->get_nodoDato()->get_dato()>pivot)cc++;
                // en el momento en que i, que es el dato "antes" del pivote, sea igual o haya pasado a j, que es el dato "despues" del pivote, sale del for porque
                // quiere decir que ya se ordenaron los datos para este pivote
                if(i>=j)break;
                swapDatoNodosLista(a.atPos(i),a.atPos(j));
                cm=cm+3;   
            }
            // Coloca el pivote en su posicion correcta
            swapDatoNodosLista(a.atPos(i),a.atPos(ultimo));
            cm=cm+3;
            // Ordena la parte izquierda al pivote
            ordenaQS(a,primero,i-1);
            // Ordena la parte derecha al pivote
            ordenaQS(a,i+1,ultimo);
        }
    return cc;
}

/*
! MAIN
*/

int main(int argc, char *argv[]) {
    Lista<string>* list = new Lista<string>();
    arbol<string> ArbolAlfabetico;
    Lista<string>* alphabeticalList = new Lista<string>();
    arbol<string> ArbolReps;
    int compSelDir = 0;
    int compQS = 0;
    switch (identifyWords(list, ArbolAlfabetico)) {
        case 0:
            cout << "ERROR: no se pudo abrir el archivo" << endl;
            return 0;
            break;
        case -1:
            cout << "ERROR: el archivo esta vacio" << endl;
            return 0;
            break;
        case 1:
            cout << "PALABRAS VERIFICADAS CON EXITO" << endl;
            break;
    }
    ofstream outFile1("../results/1_Lista_original.txt");
    ofstream outFileA("../results/2_ArbolAlfabetico.txt");
    ofstream outFile2("../results/3_Lista_alfabetica.txt");
    ofstream outFile3("../results/4_Lista_repeticiones_SD.txt");
    ofstream outFile4("../results/5_ArbolAcceso.txt");
    ofstream outFile5("../results/6_Lista_alfabetica_QS.txt");
    ofstream outFileAll("../results/AllData.txt");
    if (!outFile1 || !outFile2 || !outFile3 || !outFile4 || !outFileAll|| !outFile5 || !outFileA) {
        cerr << "Error abriendo uno de los archivos" << endl;
        return 1;
    }
    // Parte 1
    outFile1 << "--------------------------LISTA v1 (orden de aparicion)--------------------------" << endl;
    outFileAll << "--------------------------LISTA v1 (orden de aparicion)--------------------------" << endl;
    rotarLista(list);
    list->impreRep(outFile1);
    list->impreRep(outFileAll);
    outFile1 << "Cabeza (primera palabra anadida): " << list->cabeza() << endl;
    outFileAll << "Cabeza (primera palabra anadida): " << list->cabeza() << endl;
    outFile1 << "Last (ultima palabra anadida): " << list->last() << endl;
    outFileAll << "Last (ultima palabra anadida): " << list->last() << endl;
    outFile1 << "Palabras diferentes (tamano de la lista): " << list->size() << endl;
    outFileAll << "Palabras diferentes (tamano de la lista): " << list->size() << endl;
    outFile1 << "============================================================" << endl;
    outFileAll << "============================================================" << endl;
    // Parte 2
    outFileA << "------------------Arbol Recorrido Alf (IRD)-----------------" << endl;
    outFileAll << "------------------Arbol Recorrido Alf (IRD)-----------------" << endl;
    ArbolAlfabetico.IRD(outFileA);
    ArbolAlfabetico.IRD(outFileAll);
    outFileA << "============================================================" << endl;
    outFileAll << "============================================================" << endl;
    // Parte 3
    outFile2 << "--------------------LISTA v2 (Alfabetica)-------------------" << endl;
    outFileAll << "--------------------LISTA v2 (Alfabetica)-------------------" << endl;
    ArbolAlfabetico.GenLista_IRD(alphabeticalList);
    rotarLista(alphabeticalList);
    alphabeticalList->impreAlf(outFile2);
    alphabeticalList->impreAlf(outFileAll);
    outFile2 << "Cabeza: " << alphabeticalList->cabeza() << endl;
    outFileAll << "Cabeza: " << alphabeticalList->cabeza() << endl;
    outFile2 << "Last: " << alphabeticalList->last() << endl;
    outFileAll << "Last: " << alphabeticalList->last() << endl;
    outFile2 << "Palabras diferentes (tamano de la lista): " << alphabeticalList->size() << endl;
    outFileAll << "Palabras diferentes (tamano de la lista): " << alphabeticalList->size() << endl;
    outFile2 << "============================================================" << endl;
    outFileAll << "============================================================" << endl;
    // Parte 4
    outFile3 << "--------------------LISTA v3 (Repeticiones)-------------------" << endl;
    outFileAll << "--------------------LISTA v3 (Repeticiones)-------------------" << endl;
    compSelDir = selDirReps(list);
    outFile3 << "Cantidad de Comparaciones SelDir: " << compSelDir << endl;
    outFileAll << "Cantidad de Comparaciones SelDir: " << compSelDir << endl;
    rotarLista(list);
    setBinaries(list);
    list->impreRep(outFile3);
    list->impreRep(outFileAll);
    outFile3 << "Cabeza (palabra con mas repeticiones): " << list->cabeza() << endl;
    outFileAll << "Cabeza (palabra con mas repeticiones): " << list->cabeza() << endl;
    outFile3 << "Last (palabra con menos repeticiones): " << list->last() << endl;
    outFileAll << "Last (palabra con menos repeticiones): " << list->last() << endl;
    outFile3 << "Palabras diferentes (tamano de la lista): " << list->size() << endl;
    outFileAll << "Palabras diferentes (tamano de la lista): " << list->size() << endl;
    outFile3 << "============================================================" << endl;
    outFileAll << "============================================================" << endl;
    // Parte 5
    outFile4 << "------------------Hojas Arbol de Acceso-----------------" << endl;
    outFileAll << "------------------Hojas Arbol de Acceso-----------------" << endl;
    GenArbolDeAcceso(list, ArbolReps);
    ArbolReps.MostrarHojasRep(outFile4);
    ArbolReps.MostrarHojasRep(outFileAll);
    outFile4 << "============================================================" << endl;
    outFileAll << "============================================================" << endl;
    // Parte 6
    outFile5 << "--------------------------LISTA v4 (Alfabetica) --------------------------" << endl;
    outFileAll << "--------------------------LISTA v4 (Alfabetica) --------------------------" << endl;
    compQS = ordenaQS(ArbolReps, 1, list->size());
    outFile5 << "Cantidad de Comparaciones QS: " << compQS << endl;
    outFileAll << "Cantidad de Comparaciones QS: " << compQS << endl;
    list->impreAlf(outFile5);
    list->impreAlf(outFileAll);
    outFile5 << "Cabeza: " << list->cabeza() << endl;
    outFileAll << "Cabeza: " << list->cabeza() << endl;
    outFile5 << "Last: " << list->last() << endl;
    outFileAll << "Last: " << list->last() << endl;
    outFile5 << "Palabras diferentes (tamano de la lista): " << list->size() << endl;
    outFileAll << "Palabras diferentes (tamano de la lista): " << list->size() << endl;
    outFile5 << "============================================================" << endl;
    outFileAll << "============================================================" << endl;
    
    // Cierra todos los archivos
    outFile1.close();
    outFile2.close();
    outFile3.close();
    outFile4.close();
    outFile5.close();
    outFileAll.close();
}