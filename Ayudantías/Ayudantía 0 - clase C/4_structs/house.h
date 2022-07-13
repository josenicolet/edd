/*****************************************************************************/
/*                                 Casa                                      */
/*****************************************************************************/
/*                                                                           */
/* Una Casa tiene varios elementos                                           */
/*****************************************************************************/

// Indica que este archivo solo se debe incluir una vez en la compilación
#pragma once
#include <stdlib.h>
#include <stdio.h>

// Declaramos el struct para la casa
struct house;
// Definimos un alias para el struct casa.
// La sintaxis es "typedef tipo alias"
typedef struct house House;

// Definimos el struct casa y sus componentes.
// En python esto lo conocemos como los atributos de un objeto.
struct house
{
  // El número de la calle
  int streetNumber;
  // cantidad de personas que viven
  int people;
  // El ancho de la casa
  int width;
};

// Declaramos las funciones asociadas

// Inicializa una casa con las indicaciones utilizando malloc
House* house_init_malloc(int streetNumber, int people, int width);

// Inicializa una casa con las indicaciones utilizando malloc
// con notación un poco distinta_2
House* house_init_malloc_2(int streetNumber, int people, int width);

// Inicializa una casa con las indicaciones utilizando calloc
House* house_init_calloc(int streetNumber, int people, int width);

// Imprime una casa y su información
void print_house(House* house);

// Se libera la memoria utilizada por la casa
void destroy_house(House* house);

