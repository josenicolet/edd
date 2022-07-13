// Importamos el módulo estandar de input / output
#include <stdio.h>

/** La función main ES EL PROGRAMA */
int main(int argc, char** argv)
{
  // vamos a hacer una matriz de 10 * 10
  // C nos permite hacer matrices no necesariamente cuadradas
  // incluso pueden tener filas de distinto largo

  
  //Declaramos el array matrix que guarda punteros a int (int*)
  int** matrix = malloc(sizeof(int*) * 10);


  // vamos a generar los sub arrays
  for (int i = 0; i < 10; i++) {

    // creamos un array de ints
    int* int_array_i = malloc(10);

    // guardamos dicho puntero en el array matrix
    matrix[i] = int_array_i;

  }

  // tenemos nuestra matriz creada, sin embargo no tiene valores
  // inicializados.
  // Solamente le hemos asignado memoria
  // Inicializemos la posición (0,0) y (9,9)

  matrix[0][0] = 1;
  matrix[9][9] = 2;

  // ahora podemos imprimir valores 
  printf("(0,0) vale:%i\n", matrix[0][0]);
  printf("(9,9) vale:%i\n", matrix[9][9]);
  
  return 0;
}
