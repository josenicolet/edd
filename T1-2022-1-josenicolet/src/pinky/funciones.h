#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nodo.h"


void insertar_nodo(Nodo* padre, Nodo* nodo);

Nodo* buscar_nodo(Nodo* raiz, int valor, int id);

void path(Nodo* raiz, int valor, FILE* file);

void deep(Nodo* raiz, int valor, FILE* file);

void orden(Nodo* raiz, FILE* file);

//cuento cunatos nodos destruyo
int contar_subarbol(Nodo* nodo, int suma);

bool destroy(Nodo* raiz, int valor, FILE* file);