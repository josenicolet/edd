#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../engine/math/geometry.h"
#include "../engine/math/vector.h"
#include "../engine/particle.h"

// se define el struct
typedef struct caja
{
  struct caja* hijo_izq;
  struct caja* hijo_der;
  struct caja* padre;
  Segment* segmentos;
  int nivel;
  double x_1;
  double x_2;
  double y_1;
  double y_2;
  int cant_segments;
  double mediana;
} Caja;

// funciones
// de inicializacion
Caja* caja_init(double x_1, double x_2, double y_1, double y_2, int cant_segments);

//partition
int partition(double* medias_segmentos, int inicio, int final);

//median
int buscar_mediana(Caja* caja_raiz, double* medias_segmentos);

// segmentar caja
void segmentar_caja(Caja* caja_raiz, char eje);

//buscar medidas de una caja
void medidas(Segment* segmentos, int cant_segmentos, double* medidas);

//segmentar cajas
void crea_arbol(Caja* caja_raiz, char eje);

//revisar si la particula colisiona
Caja* colision(Caja* caja_raiz, Particle particula, double x_min, double x_max, double y_min, double y_max, char eje);

//retorna el segmento cn el cual colisiona
void colisiona(Caja* caja_raiz, Particle* particula, double x_min, double x_max, double y_min, double y_max, char eje);

// destruir
void caja_destroy(Caja* caja);
