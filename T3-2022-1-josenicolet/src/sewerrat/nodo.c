#include "nodo.h"

Nodo* nodo_init(int id, int x, int y)
{ 
    //necesito memoria
    Nodo* nodo = malloc(sizeof(Nodo));
    // cambio los valores
    *nodo = (Nodo){
        .x = x,
        .y = y,
        .id = id,
        .representante = id,
        //.aristas = 0,
    };

    // se retorna el nodo
    return nodo;

}

// destruir
void nodo_destroy(Nodo* nodo)
{
    free(nodo);
}