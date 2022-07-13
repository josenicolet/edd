#pragma once

// Declaramos el struct para la matriz
struct matrix;
// Definimos un alias para el struct matriz.
// La sintaxis es "typedef tipo alias"
typedef struct matrix Matrix;

// Definimos el struct matriz
struct matrix
{
  /** La matriz en si: un arreglo de arreglos */
  int** matrix;
  /** El alto de la matriz */
  int height;
  /** El ancho de la matriz */
  int width;
};

Matrix* matrix_init(int height, int width);

void matrix_print(Matrix* mat);

/** Libera los recursos asociados a esta matriz */
void matrix_destroy(Matrix* mat);