/*****************************************************************************/
/*                                 Structs                                   */
/*****************************************************************************/
/*                                                                           */
/* En C podemos definir nuestros propios tipos de datos, parecidos a las     */
/* clases, llamados Struct. La unica diferencia que tienen con las clases    */
/* es el hecho de que no tienen funciones, por lo que cualquier operación    */
/* que queramos hacer con ellos requerirá que los pasemos como parámetro.    */
/* Esto último es similar al self de python (porque de aquí viene)           */
/*                                                                           */
/* Para organizarnos, definimos los structs y declaramos las funciones       */
/* externas en un archivo llamado header .h, mientras que en un archivo .c   */
/* aparte escribimos el codigo de esas funciones y funciones internas.       */
/* El .h es la cara visible de tu struct, como si fuera una librería.        */
/* Es lo primero que la gente va a leer si quiere utilizar la estructura     */
/* que definiste, sin tener que ponerse a leer el código de las funciones    */
/* Revisa los archivos .h y .c que están junto a este para tener un ejemplo. */
/*                                                                           */
/* Como aclaración:                                                          */
/* Si S es un struct en STACK que tiene los elementos a y b, podemos acceder */
/* a ellos usando S.a y S.b. En cambio si P es un puntero a un struct de ese */
/* mismo tipo, se accede a los elementos con P -> a y P -> b                 */
/*****************************************************************************/

#include <stdio.h>
#include <stdbool.h>
// Importamos la casa
#include "house.h"

int main(int argc, char** argv)
{
  /*
  Podemos definir directamente el struct en el stack.
  Declarar la casa en el stack automaticamente le otorga memoria
  a la casa
  */
  House stackHouse;
  stackHouse.people = 5;
  stackHouse.streetNumber = 10;
  stackHouse.width = 15;


  // prints de la casa
  printf("### Esta es la casa en el stack ###\n");
  printf("numero de personas: %i\n", stackHouse.people);
  printf("numero de calle: %i\n", stackHouse.streetNumber);
  printf("ancho: %i\n\n", stackHouse.width);


  // Otra (mejor) opción es guardar la casa en el heap utilizando malloc
  House* heapHouse = malloc(sizeof(House));
  // aquí utilizamos flechas, pues estamos alterando el
  // struct utilizando su puntero
  heapHouse -> people = 6;
  heapHouse -> streetNumber = 12;
  heapHouse -> width = 15;
  // prints de la casa
  printf("### Esta es la casa en el heap ###\n");
  printf("numero de personas: %i\n", heapHouse->people);
  printf("numero de calle: %i\n", heapHouse->streetNumber);
  printf("ancho: %i\n\n", heapHouse->width);


  // Y otra opción (más ordenada) es almacenar en una función
  House* heapFunctionHouse = house_init_malloc(5, 12, 13);
  print_house(heapFunctionHouse);

  // También es posible utilizar calloc, pero preferimos malloc
  House* heapFunctionHouseCalloc = house_init_calloc(7, 24, 25);
  print_house(heapFunctionHouseCalloc);

  destroy_house(heapHouse);
  destroy_house(heapFunctionHouse);
  destroy_house(heapFunctionHouseCalloc);
  return 0;
}