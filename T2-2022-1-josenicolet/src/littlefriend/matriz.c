#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

/** Inicializa una matriz aleatoria con las dimensiones especificadas */
Matrix* matrix_init(int height, int width)
{
  Matrix* mat = malloc(sizeof(Matrix));
  mat -> height = height;
  mat -> width = width;
  // La definimos como un arreglo de filas: cada fila es un arreglo de ints
  mat -> matrix = calloc(height, sizeof(int*));
  for(int row = 0; row < height; row++)
  {
    // Cada fila tiene el ancho de la matriz
    mat -> matrix[row] = calloc(width, sizeof(int));
  }
  return mat;
}

void matrix_print(Matrix* mat)
{
  for(int row = 0; row < mat -> height; row++)
  {
    for(int col = 0; col < mat -> width; col++)
    {
      printf("%i ",mat -> matrix[row][col]);
    }
    printf("\n");
  }
}

/** Libera los recursos asociados a esta matriz */
void matrix_destroy(Matrix* mat)
{
  for(int row = 0; row < mat -> height; row++)
  {
    // Primero liberamos las filas una por una
    free(mat -> matrix[row]);
  }
  // Luego el arreglo de filas
  free(mat -> matrix);
  // Y por ultimo el struct en si
  free(mat);
}