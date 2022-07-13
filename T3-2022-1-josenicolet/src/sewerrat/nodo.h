#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo
{
  int x;
  int y;
  int id;
  int representante;
  //int aristas;
} Nodo;


Nodo* nodo_init(int id, int x, int y);

// destruir
void nodo_destroy(Nodo* nodo);
