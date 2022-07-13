#include "house.h"

/*
En python, tu asignabas un valor a una vairable (un int, bool, etc) y se guardaba.
En C, debes indicar cómo guardar la información usando funciones de stdlib.h
Esas funciones son malloc, calloc y free. Estas funciones interactúan con el HEAP.
Más abajo te enseñamos a utilizar estos bloques de memoria y a liberarlos cuando ya
no los necesites.
*/

/* ########## Almacenar utilizando malloc ########## */
House* house_init_malloc(int streetNumber, int people, int width)
{
  House* house = malloc(sizeof(House));

  *house = (House) {
    .streetNumber = streetNumber,
    .people = people,
    .width = width,
  };
  return house;
}

/* ########## Almacenar utilizando malloc 2 ########## */
House* house_init_malloc_2(int streetNumber, int people, int width)
{
  House* house = malloc(sizeof(House));

  house -> streetNumber = streetNumber;
  house -> people = people;
  house -> width = width;

  return house;
}

/* ########## Almacenar utilizando calloc ########## */
House* house_init_calloc(int streetNumber, int people, int width)
{
  House* house = calloc(1, sizeof(House));

  *house = (House) {
    .streetNumber = streetNumber,
    .people = people,
    .width = width,
  };
  return house;
}

/* ########## Imprimir la casa ########## */
void print_house(House* house)
{
  printf("### Esta es la casa en el heap utilizando funciones ###\n");
  printf("Numero de personas: %i\n", house->people);
  printf("Numero de calle: %i\n", house->streetNumber);
  printf("Ancho: %i\n\n", house->width);
}

/* ########## Liberar memoria con free ########## */
void destroy_house(House* house)
{
  free(house);
}