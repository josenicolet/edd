#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "nodo.h"

typedef struct arista
{
  Nodo* nodo1;
  Nodo* nodo2;
  int distancia;
} Arista;


Arista* arista_init(Nodo* nodo1, Nodo* nodo2, int distancia);

int partition(Arista** aristas, int inicio, int final);

void quicksort(Arista** aristas, int inicio, int final);

// destruir
void arista_destroy(Arista* arista);