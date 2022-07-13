#include "nodo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//inicializacion de nodo

Nodo* nodo_init(int id, int valor)
{ 
    //necesito memoria
    Nodo* nodo= malloc(sizeof(Nodo));
    // cambio los valores
    *nodo = (Nodo){
        .id = id,
        .valor = valor,
        .hijo_izq = NULL,
        .hijo_der = NULL,
        .padre = NULL,
        .nivel = 0,
        .camino_mayor = 0,
        .camino_menor = 0,
    };

    // se retorna el nodo
    return nodo;

}



// destruir
void nodo_destroy(Nodo* nodo)
{
    //si tiene hijos destruyo los hijos
    // if (nodo->hijo_izq)
    // {
    //     nodo_destroy(nodo->hijo_izq);
    // }
    // if (nodo->hijo_der)
    // {
    //     nodo_destroy(nodo->hijo_der);
    // }
    //destruyo material
    free(nodo);
}