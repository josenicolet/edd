// Importamos el módulo estandar de input / output
#include <stdio.h>

int main(int argc, char** argv)
{

    /*
        Recordemos que C es un lenguaje fuertemente tipado, por lo que se tienen
        los siguientes tipos de datos básicos.

        Noten como
    */

    // int representa un número entero

        int x = 1234;
        printf("X = %i\n", x);

    // char representa un carácter, y se escribe con comillas simples
        char y = 'h';
        printf("Y = %c\n", y);

    // float representa números decimales

        float z = 2.72181;
        printf("Z = %f\n", z);
    
    // double son números decimales con más precision
        double z2 = 122189.128391;
        printf("Z2 = %lf\n", z2);

    /*
        Asimismo, las variables que representan algún tipo de dato, siempre tendrá 
        la misma cantidad de bytes en memoria
    */

    // Imprimimos cual es el tamaño de un int en bytes
        printf("Size of INT: %zu\n", sizeof(int));

    // Imprimimos cual es el tamaño de un char en bytes
        printf("Size of CHAR: %zu\n", sizeof(char));

    // Imprimimos cual es el tamaño de un int en bytes
        printf("Size of FLOAT: %zu\n", sizeof(float));

    // Imprimimos cual es el tamaño de un int en bytes
        printf("Size of DOUBLE: %zu\n", sizeof(double));

  /////////////////////////////////////////////////////////////////////////////

  // Una variable en el computador es simplemente una secuecia de 0s y 1s

  // Los tipos nos dicen como interpretar eso.

  // Veamos que pasa si tomamos una variable y la interpretamos
  // (incorrectamente) como si fuera de otro tipo

  printf("Z = 2.721810 interpretado como int: %i\n", z);

  // Nótese que interpretar char como un numero entero es perfectamente legal

  printf("Y = 'h' interpretado como int: %i\n", y);

  // Incluso podemos asignarle valores numéricos:

  y = 105;

  printf("Y = 105 interpretado como int: %i\n", y);
  printf("Y = 105 interpretado como char: %c\n", y);

  // Y operar sobre el como si fuera un número

  y = y - 1;
  printf("Y = 104 interpretado como char: %c\n", y);

  /////////////////////////////////////////////////////////////////////////////

  // OJO: Las división de dos numeros enteros entrega como resultado un numero entero

  double r = 5 / 3;

  printf("5 / 3 = %lf\n", r);

  // Si necesitamos interpretar correctamente un valor de un tipo como otro debemos usar CASTING

  r = (double) 5 / (double) 3;

  printf("5 / 3 con casting = %lf\n", r);

  // Basta con que uno de los dos sea double para que la operacion sea correcta

  r = (double) 5 / 3;

  printf("5 / 3 con un solo cast = %lf\n", r);
  
  return 0;
} 