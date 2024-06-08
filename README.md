# TP2-Algoritmos

Este programa toma un archivo .txt, el cual solo puede contener caracteres en ASCII del 0 al 127 (es decir, no puede contener letras con tilde por ejemplo), identifica todas las palabras diferentes de su contenido, las va contando y las almacena en una lista.
A lo largo del programa, se construye un arbol binario siguiendo un orden alfabetico de las palabras encontradas y a partir del cual se crea otra lista, se ordena a la lista original por repeticiones y se le asigna a cada palabra un codigo binario, se crea un arbol de acceso logaritmico a la lista por repeticiones, y finalmente se ordena alfabeticamente a la lista ordenada por repeticiones accediendo a traves del arbol de acceso.
Al final, se obtienen logs que muestran los diferentes elementos creados a lo largo del programa.

El objetivo de un programa como este es comprimir archivos de texto. La idea seria tomar la lista ordenada por repiticiones, construir una especie de tabla asociada que permita convertir de una palabra a un numero binario o viceversa, y programar los metodos que realicen la conversión de una forma a la otra tomando dicha tabla como referencia.
