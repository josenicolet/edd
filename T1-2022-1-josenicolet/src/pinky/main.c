#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nodo.h"
#include "funciones.h"


/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    exit(1);
  }

  return true;
}



// bool ver_balance(Nodo* nodo)
// {
//   int camino_mayor = 0;
//   int camino_menor = 20;
//   if (nodo->hijo_izq)
//   {
//     //si tiene hijo izquierdo
//     bool bal = ver_balance(nodo->hijo_izq);
//     if (camino_mayor < nodo->hijo_izq->camino_mayor + 1)
//     {
//       camino_mayor = nodo->hijo_izq->camino_mayor + 1;
//     }
//     if (camino_menor > nodo->hijo_izq->camino_menor + 1)
//     {
//       nodo->camino_menor = nodo->hijo_izq->camino_menor + 1;
//     }
//   }
//   if (nodo->hijo_der)
//   {
//     //si tiene hijo derecho
//     bool bal1 = ver_balance(nodo->hijo_der);
//     if (camino_mayor < nodo->hijo_der>camino_mayor + 1)
//     {
//       camino_mayor = nodo->hijo_der->camino_mayor + 1;
//     }
//     if (camino_menor > nodo->hijo_der->camino_menor + 1)
//     {
//       nodo->camino_menor = nodo->hijo_der->camino_menor + 1;
//     }
//   }
//   nodo->camino_mayor = camino_mayor;
//   nodo->camino_menor = camino_menor;
//   if ((camino_mayor - camino_menor) < 2)
//   {
//     return true;
//   }
//   else
//   {
//     return false;
//   }
// }

int main(int argc, char** argv) {
    check_arguments(argc, argv);

    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");

    int criteria;
    int node_count;
    int query_count;
    /* leemos el criterio para armar el arbol */
    fscanf(input_file, "%d", &criteria);

    fscanf(input_file, "%d", &node_count);

    /* leemos Cada nodo */
    // lista de materiales
    Nodo** nodos = calloc(node_count, sizeof(Nodo*));
    //Material** materiales = calloc(node_count, sizeof(Material*));
    int index, conductivness, hardness, inatorness;
    for(int i=0; i<node_count; i++){
        fscanf(input_file, "%d %d %d %d", &index, &conductivness, &hardness, &inatorness);
        printf("%d %d %d %d\n", index, conductivness, hardness, inatorness);
        //materiales[i] = material_init(i, index, conductivness, hardness, inatorness);
        Nodo* nodo = NULL;
        if (criteria == 0)
        {
          nodo = nodo_init(i, index);
        }
        else if (criteria == 1)
        {
          nodo = nodo_init(i, conductivness);
        }
        else if (criteria == 2)
        {
          nodo = nodo_init(i, hardness);
        }
        else if (criteria == 3)
        {
          nodo = nodo_init(i, inatorness);
        }
        nodos[i] = nodo;
    }
    Nodo* raiz = nodos[0];
    for (int i = 1; i < node_count; i++)
    {
      //por cada nodo de la lista (que no este en el arbol)
      Nodo* insertar = nodos[i];
      Nodo* padre = buscar_nodo(raiz, insertar->valor, insertar->id);
      //tengo a que padre lo inserto
      insertar_nodo(padre, insertar);
      // //ver si está balanceado
      // int cant_padres = insertar->nivel;
      // Nodo* actual = insertar
      // for (int i = 0; i < 3; i++)
      // {
      //   Nodo* padre_actual = actual->padre;
      //   bool* balance = ver_balance(padre_actual);
      //   if (balance == true)
      //   {
      //     //esta balanceado busco en el otro papa
      //     actual = actual->padre;
      //   }
      //   else 
      //   { 
      //     //no está balanceado lo balanceo
      //     //el hijo toma el lugar del padre
      //   }
      // }

      //hasta ahora, por cada nodo en la lisat nodos lo inserto segun si es mayor o menor
      // al nodo raiz, que es el primero de la lista

    }

    //ahora las operaciones

    fscanf(input_file, "%d", &query_count);
    /* leemos las consultas */
    char command[32];
    int value;
    for(int i=0; i<query_count; i++){
        fscanf(input_file, "%s %d", command, &value);
        printf("%s %d\n", command, value);
        /* completar la revision de comando y ejecucion de los mismos */
        if (string_equals(command, "PATH"))
        {
          // busco el path
          path(raiz, value, output_file);
        }
        else if (string_equals(command, "DEEP"))
        {
          //imprimo el nivel
          deep(raiz, value, output_file);
        }
        else if (string_equals(command, "ORDER"))
        {
          //retornar valores ordenado a no mas de o(n)
          orden(raiz, output_file);
          fprintf(output_file, "\n");
        }
        else if (string_equals(command, "DESTROY"))
        {
          //destruir el subarbol de el nodo con ese valor
          //incluyendolo a el
          bool devuelvo = destroy(raiz, value, output_file);
          if (devuelvo == false)
          {
            fprintf(output_file, "%i\n", 0);
          }

        }
    }

    //liberar nodos
    for (int i = 0; i < node_count; i++)
    {
      Nodo* nodo = nodos[i];
      nodo_destroy(nodo);
    }
    free(nodos);

    fclose(input_file);
    fclose(output_file);
    return 0;
}

