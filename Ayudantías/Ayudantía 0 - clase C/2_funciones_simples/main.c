#include <stdio.h>

/*

    La estructura general de una función es:

    type function_name (type_1 parameter_1, ...)
    {
        // código de función
    }

    Antes de seguir con las funciones debemos ver que significa declarar y definir

    DECLARAR:

    type function(type_1 parameter_1, ...);

    DEFINIR:

    type function(type_1 parameter_1, ...)
    {
        // código de la función
    }
    
    Definir una función la declara también.

*/

// Se declara la función
void mi_primera_funcion();

// Se define
void mi_primera_funcion()
{
    printf("Hello World\n"); // No olvidar salto de Línea
}

int sumar(int a, int b);

int sumar(int a, int b)
{
  int c = a + b;
  return c;
}

// Función que cuenta los divisores de un número  n
int div_count(int n);

int div_count(int n){
  
  int count = 0;

  for (int i = 1; i <= n; i++)
  {
    if (n % i == 0)
    {
        count += 1;
    }
  }

  return count;
}

int main(int argc, char** argv)
{
    mi_primera_funcion();

    int d = sumar(2, 3);

    int div = div_count(15);

    printf("d = %i\n", d);

    printf("15 tiene %d divisores\n", div);

    return 0;
}