#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "cuadrado.h"
#include "hashtable.h"
#include "matrix.h"


void check_args(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s input querys output\n", argv[0]);
        exit(1);
    }
}

int main(int argc, char *argv[]){
    check_args(argc, argv);
    printf("Hello Little\n");

    // extraigo lo que necesito
    FILE *input_file = fopen(argv[1], "r");
    FILE *queries_file = fopen(argv[2], "r");
    FILE *output_file = fopen(argv[3], "w");

    //leemos la dimension de la grilla
    int dimension;
    fscanf(input_file, "%d", &dimension);
    int cant_queries;
    fscanf(queries_file, "%d", &cant_queries);

    //arregl de todos los nuemro de color de los pixeles
    int cant_pixeles = dimension * dimension;
    Matrix* matrix_pixeles = matrix_init(dimension, dimension);
    //tengo una matriz llena de ceros
    //printf("dimension %d \n", dimension);

    //leemos todas las filas
    for (int f = 0; f < dimension; f++)
    {
        // por cada fila
        for (int c = 0; c < dimension; c++)
        {
            // cada caracter
            int color;
            fscanf(input_file, "%d", &color);
            matrix_pixeles->matrix[f][c] = color;
            //printf( "%d ", color);
        }
        //printf("\n");
    }
    //tengo mi matriz con los coles de los pixeles

    //veo las matrices de las queries

    int cant_cuadrados = 0;
    //cuentos cuantos cuadrados totales voy a tener
    for (int d = 1; d <= dimension; d++)
    {
        cant_cuadrados += d*d;
    }
    //se hace un arreglo de todos los cuadrados o hashes que tendre
    //Cuadrado* cuadrados[cant_cuadrados];
    //int cuadrados_agregados = 0;

    //creo tabla
    Hashitem** table = calloc(256 + dimension, sizeof(Hashitem*));
    int cont_cuadrados = 0;
    //por cada pixel tengo qque agrandar el cuadrado
    for (int f = 0; f < dimension; f++)
    {
        //por cada fila
        for (int c = 0; c < dimension; c++)
        {
            //por cada pixel
            int pixel_actual = matrix_pixeles->matrix[f][c];
            int cant_cuadrados_pixel;
            if (f > c)
            {
                //si la fila es mayor a la columna
                cant_cuadrados_pixel = dimension - f;
            }
            else
            {
                //columna es mayor, o son iguales
                cant_cuadrados_pixel = dimension - c;
            }

            //Cuadrado* cuadrado_anterior = NULL; //hash anterior?
            Hashitem* hash_anterior = NULL;
            float hash_anterior_funcion;
            //tengo la cantidad de cuadrados que voy a hacer agrandano hacia abajo y a la derecha el pixel
            for (int i = 1; i <= cant_cuadrados_pixel; i++)
            {
                //por cada cuadrado que tengo que hacer
                // tengo su dimension i
                //y su pixel inical
                //que es lo que guardo en el hash
                float hash;
                Hashitem* agrego;
                if (i != 1)
                {
                    //si la dimension del cuadrado creado es distindo de 1 tiene anterior para usar el hash pasado
                    //calculo el hash con el pasado
                    //se hace un arreglo de los numero a agregar
                    //primero calculo cunatos agregar
                    // se la dimension anterior i-1 y la actual i
                    int cant_pixeles_anterior = (i-1)*(i-1);
                    int cant_agregar = (i*i) - cant_pixeles_anterior;
                    int pixel[cant_agregar];
                    //int fila_inicial = f;
                    //int columna_inicial = c;
                    int fila_inicial = hash_anterior->fila_inicial;
                    int columna_inicial = hash_anterior->columna_inicial;
                    int mitad = (int) cant_agregar/2; //parte entera de la mitad
                    int nueva_fila = fila_inicial + i - 1; //fila en la qeu saco nuevos
                    int nueva_col = columna_inicial + i - 1;
                    int contador_agregados = 0;
                    //arreglo de contidad de pixeles a agregar
                    //siempre tengo la misma fila y columna inicial porque estoy agrandando del mismo pixel
                    //float promedio = 0;
                    for (int i = 0; i < mitad; i++)
                    {
                        //por cada uno de los que tengo que agregar
                        //promedio += matrix_pixeles->matrix[nueva_fila][columna_inicial + i];
                        pixel[contador_agregados] = matrix_pixeles->matrix[nueva_fila][columna_inicial + i];
                        contador_agregados += 1;
                    }
                    for (int i = 0; i < mitad + 1; i++)
                    {
                        //lo que me faltan agregar más 1
                        //promedio += matrix_pixeles->matrix[fila_inicial + i][nueva_col];
                        pixel[contador_agregados] = matrix_pixeles->matrix[fila_inicial + i][nueva_col];
                        contador_agregados += 1;
                    }
                    //tengo el arreglo de los nuevos que agrege
                    //saco el promedio de esos cn el hash

                    float promedio = hash_function(pixel, cant_agregar);
                    float suma_anterior = hash_anterior_funcion * (i-1) * (i-1);
                    float suma_actual = promedio * cant_agregar;
                    //float suma = promedio + suma_anterior;
                    float suma = suma_actual + suma_anterior;
                    hash = (float) suma / (i * i); //suma total dividido la cantidad total
                    agrego = insert(table, hash, i, f, c);
                    cont_cuadrados += 1;
                }
                else
                {
                    //si es un cuadrado unitario hago el hash solo con ese que es el pixel actual
                    //le hago la funcion de hash que es sacar el promdio
                    int pixel[i];
                    pixel[0] = pixel_actual;
                    hash = hash_function(pixel, 1);
                    //lo guardo en la tabla de  hash
                    agrego = insert(table, hash, 1, f, c);
                    cont_cuadrados += 1;
                }
                //ya definido el anterior cambio el hash anterior
                //printf("hice el cuadrado numer %d, que tiene fila %d, columna %d, dimension %d y proemdio %f \n", cont_cuadrados, agrego->fila_inicial, agrego->columna_inicial, agrego->dimension, hash);
                hash_anterior = agrego;
                hash_anterior_funcion = hash;
                // cambio el hash anterior a null y parto denuevo en el otro pixel
                if (i == cant_cuadrados_pixel)
                {
                    //es el ultimo antes de cambiar de pixel y ya le definí su anterior
                    hash_anterior = NULL;
                    hash_anterior_funcion = 0;
                }


                
            }
            // lo agrego a la tabla de hash 
            //tengo que ir agrandando los cuadrados y agregandolos a la tabla de hash
        }
    }
    //agrande todos los pixeles, ahora tengo la tabla lista con clave el promedio de todos
    //tengo que leer cada consulta
    printf("se hizo la tabla");
    for (int q = 0; q < cant_queries; q++)
    {
        //por cada query
        int dimension_query;
        fscanf(queries_file, "%d", &dimension_query);
        Matrix* matrix_query = matrix_init(dimension_query, dimension_query);
        //leemos todas las filas
        int cant_pixeles_query = dimension_query * dimension_query;
        int arreglo_pixeles[cant_pixeles_query];
        //printf("query n %d de %d \n", q, cant_queries);
        int contador = 0;
        for (int f = 0; f < dimension_query; f++)
        {
            // por cada fila
            for (int c = 0; c < dimension_query; c++)
            {
                // cada caracter
                int color_query;
                fscanf(queries_file, "%d", &color_query);
                matrix_query->matrix[f][c] = color_query;
                arreglo_pixeles[contador] = color_query;
                contador += 1;
                //printf( "%d ", color_query);
            }
            //printf("\n");
        }
        //matrix_print(matrix_query);
        //matrix_print(matrix_pixeles);
        //tengo la matriz de la query hecha
        //busco su primedio
        float prom_query = hash_function(arreglo_pixeles, cant_pixeles_query);
        int promedio_query = (int) prom_query;
        printf("proemdio de la query numero %d de %d es %d y su dimension %d \n", q, cant_queries, promedio_query, dimension_query);
        //tengo el promedio de la query y lo busco en la tabla
        int cant_query = buscar_query(table, promedio_query, dimension_query, matrix_query, matrix_pixeles);
        fprintf(output_file, "%d\n", cant_query);
    }
    return 0;
}