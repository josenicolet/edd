#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"

typedef struct hashitem
{
  int dimension;
  int fila_inicial;
  int columna_inicial;
  struct hashitem* next;
} Hashitem;

float hash_function(int* pixeles, int cant_pixeles);

//lo agrego a la tabla
Hashitem* insert(Hashitem **table, float hash, int dimension, int fila_inicial, int columna_inicial);

//busco el valor que uno quiere, devuelve la cantidad de veces que está
int buscar_query(Hashitem **table, int hash, int dimension_query, Matrix* matriz_query, Matrix* matriz);