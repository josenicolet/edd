#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct item
{
  int peso;
  int id;
  struct item* next;
} Item;


Item* item_init(int id, int peso);

void agregar_item(Item* item, Item* nuevo);

void imprimo_items(Item* item, FILE* autput);

int partition(Item** items, int inicio, int final);

void quicksort(Item** items, int inicio, int final);

void item_destroy(Item* item);