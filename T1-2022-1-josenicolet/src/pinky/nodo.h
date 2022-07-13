#pragma once

#include <stdbool.h>
// se define el struct
typedef struct nodo
{
  int id;
  //Material* material;
  int valor;
  struct nodo* hijo_izq;
  struct nodo* hijo_der;
  struct nodo* padre;
  int nivel;
  int camino_mayor;
  int camino_menor;
} Nodo;

// funciones
// de inicializacion
Nodo* nodo_init(int id, int valor);


// destruir
void nodo_destroy(Nodo* nodo);
