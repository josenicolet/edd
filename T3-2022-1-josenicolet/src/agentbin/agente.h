#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"

typedef struct agente
{
  Item* item;
  int id;
  int peso_actual;
  struct agente* next;
} Agente;


Agente* agente_init(int id, Item* item);

bool cabe_item(Item* item, Agente* agente, int capacidad);

void imprimir_agente(Agente* agente, FILE* output);

void agente_destroy(Agente* agente);