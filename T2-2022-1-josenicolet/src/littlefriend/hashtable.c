#include "hashtable.h"
#include <math.h>

float hash_function(int* pixeles, int cant_pixeles)
{
    int contador = 0;
    float promedio = 0;
    //le entrego un array con la cantidad de elementos en el y saco el promedio
    for (int i = 0; i < cant_pixeles; i++)
    {
        int color = pixeles[i];
        contador += color;
    }
    //sumo todos los int de colores y lo divido por la cantidad de pixeles sumados
    promedio = (float) contador/cant_pixeles; 
    return promedio;
}

Hashitem* insert(Hashitem **table, float hash, int dimension, int fila_inicial, int columna_inicial)
{
    // devuelvo el que acabo de agregar
    Hashitem* agrego = NULL;
    int hash_real = (int) hash;
    Hashitem* item = table[hash_real + dimension]; //el primero con ese promedio
    if (item == NULL)
    {
        //no hay cuadrado con ese promedio
        agrego = malloc(sizeof(Hashitem));
        agrego->dimension = dimension;
        agrego->fila_inicial = fila_inicial;
        agrego->columna_inicial = columna_inicial;
        agrego->next = NULL;
        table[hash_real + dimension] = agrego;
    }
    else
    {
        //si ya hay uno en ese lugar
        Hashitem* actual = item;
        while(actual->next != NULL)
        {
            //mientras no esté en el ultimo cuadrado del encadenamiento
            actual = actual->next;
            
        }
        //el actual será el final
        //lo agrego despues del final 
        agrego = malloc(sizeof(Hashitem));
        actual->next = agrego;
        actual->next->dimension = dimension;
        actual->next->fila_inicial = fila_inicial;
        actual->next->columna_inicial = columna_inicial;
        actual->next->next = NULL;
        //agregado
    }

    return agrego;
}

//busco el valor que uno quiere, devuelve la cantidad de veces que está
int buscar_query(Hashitem **table, int hash, int dimension_query, Matrix* matriz_query, Matrix* matriz)
{
    int cant = 0;
    Hashitem* item = table[hash + dimension_query];
    while (item != NULL)
    {
        //printf("hay cuadrado con promedio %d con fila %d y columna %d y dimensoin %d\n", hash, item->fila_inicial, item->columna_inicial, item->dimension);
        //mientras no este en null, paso por todos los items 
        //veo asi es el mismo cuadrado que yo estoy buscando
            //si es sumo uno a la cantidad
        if (item->dimension == dimension_query)
        {
            //printf("pasa con dim de item %d\n", dimension_query);
            //ya se que el proemdio es el mimso, entonces solo bsuco los que tienen la misma cantidad
            bool iguales = true; //por cada item con mi misma dimension
            //int cant_pixeles_query = dimension_query * dimension_query;
            for (int f = 0; f < dimension_query; f++)
            {
                if (iguales == true)
                {
                    for (int c = 0; c < dimension_query; c++)
                    {
                        //por cada pixel veo si es igual
                        int pixel_query = matriz_query->matrix[f][c];
                        int pixel_original = matriz->matrix[item->fila_inicial + f][item->columna_inicial + c];
                        if (pixel_query != pixel_original)
                        {
                            //printf("ya no son iguales\n");
                            if (hash == 79 && dimension_query == 35)
                            {
                                printf("el pixel de query era %d y, en la fila %d y columna %d el del original era %d\n", pixel_query, item->fila_inicial, item->columna_inicial, pixel_original);
                            }
                            //no son el mismo aunque tengan el mismo dimension y promedio
                            iguales = false; //ya no son iguales, no quiero seguir viendo por todos los pixeles de la querty
                            break; //termino el primer for, no el segundo, sigo paseando por filas
                        }
                        else
                        {
                            if (hash == 79 && dimension_query == 35)
                            {
                                printf("iguales-");
                            }
                        }

                    }
                }
                //termino el for de columnas
                // if (iguales == false)
                // {
                //     //no necesito seguir por las filas
                //     // if (hash == 79 && dimension_query == 35)
                //     // {
                //     //     printf("no son iguales y salgo del for\n");
                //     // }
                //     //printf("no son iguales y salgo del for\n");
                //     break;
                // }
            }
            //termino de revisar todos los pixeles de la query
            //si ya no son iguales termino el for antes y iguales es false
            if (iguales == true)
            {
                //siguen iguales despues de revisar todo
                //printf("son iguales\n");
                cant += 1;
                if (hash == 79 && dimension_query == 35)
                {
                        printf("son iguales cant %d \n", cant);
                }
            }

        }
        item = item->next;
        if (hash == 79 && dimension_query == 35)
        {
            printf("iguales-");
        }
    }
    //si el item no esta sera null y devuelvo cero altiro
    return cant;
}