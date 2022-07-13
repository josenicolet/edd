#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nodo.h"
#include "arista.h"
#include <math.h>


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

//calcular distancia
int distancia(Nodo* nodo1, Nodo* nodo2)
{
  //
  int dist = fabs(nodo1->x - nodo2->x) + fabs(nodo1->y - nodo2->y);

  return dist;
}

int main(int argc, char **argv){
    
    check_arguments(argc, argv);

    // extraigo lo que necesito
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    //leemos la dimension de la grilla
    int cant_nodos;
    fscanf(input_file, "%d", &cant_nodos);

    //Nodo** nodos[cant_nodos];
    Nodo** nodos = malloc(cant_nodos * sizeof(Nodo*));
    //inicializamos los nodos
    for (int i = 0; i < cant_nodos; i++)
    {
      int x;
      int y;
      fscanf(input_file, "%d", &x);
      fscanf(input_file, "%d", &y);
      Nodo* nodo = nodo_init(i, x, y);
      nodos[i] = nodo;
    }

    //creo todas las aristas
    int cant_aristas = (cant_nodos * (cant_nodos -1)) / 2;
    Arista** aristas = malloc(cant_aristas * sizeof(Arista*));
    //Arista** aristas[cant_aristas];
    int aristas_creadas = 0;
    int contador = 0;
    while (contador < (cant_nodos - 1))
    {
      //
      Nodo* nodo = nodos[contador];
      for (int n = contador+1; n < cant_nodos; n++)
      {
        //creo la arista
        Nodo* nodo2 = nodos[n];
        int dist = distancia(nodo, nodo2);
        Arista* arista = arista_init(nodo, nodo2, dist);
        //arista creada, la meto en la lista
        aristas[aristas_creadas] = arista;
        aristas_creadas += 1;
      }
      contador += 1;
    }
    //tengo todas las aristas creada
    //las ordeno con quicksort
    int inicio = 0;
    int final = cant_aristas - 1;
    quicksort(aristas, inicio, final);
    //el arreglo de aristas ya está ordenado

    //comienzo con kruskal
    Arista** aristas_finales = calloc( cant_nodos - 1, sizeof(Arista*));
    int aristas_agregadas = 0;
    int costo_final = 0;
    for (int a = 0; a < cant_aristas; a++)
    {
      //por cada arista de las ordenandas
      Arista* arista = aristas[a];
      // arista tiene nodo 1 y nodo 2
      //printf("tengo un nodo con rep %d y el otro con %d \n", arista->nodo1->representante, arista->nodo2->representante);
      if (arista->nodo1->representante != arista->nodo2->representante)
      {
        //si los nodos tineen distintas no hace ciclo
        //printf("son diferentes\n");
        aristas_finales[aristas_agregadas] = arista;
        aristas_agregadas += 1;
        //cunado lo agrego sumo el costo
        costo_final += arista->distancia;
        //arista->nodo1->aristas += 1;
        //arista->nodo2->aristas += 1;
        //arreglo los representantes
        int cambio;
        int menor;
        if (arista->nodo1->representante < arista->nodo2->representante)
        {
          //cambio todos con el representate mayor
          cambio = arista->nodo2->representante;
          menor = arista->nodo1->representante;
        } else {
          cambio = arista->nodo1->representante;
          menor = arista->nodo2->representante;
        }
        //los con representante cambio lo cambio por el menor
        for (int j = 0; j < cant_nodos; j++)
        {
          //reviso todos los nodos, si el nodo tiene el mimo representante que cambio
          Nodo* nodo = nodos[j];
          if (nodo->representante == cambio)
          {
            nodo->representante = menor;
          }
        }
        //printf("ahora tengo un nodo con rep %d y el otro con %d \n", arista->nodo1->representante, arista->nodo2->representante);
      }
      //
      // bool ciclo = hace_ciclo()
      // if (ciclo == false)
      // {
      //   //no hace ciclo
      //   aristas_finales[aristas_agregadas] = arista;
      //   aristas_agregadas += 1;
      // }
      // if (aristas_agregadas == cant_nodos - 1)
      // {
      //   //si ya complete las minimas
      //   break;
      // }
    }

    //tengo las arisas finales terminadas
    //las imprimo
    fprintf(output_file, "%d\n", costo_final);
    for (int j = 0; j < cant_nodos - 1; j++)
    {
      Arista* arista_final = aristas_finales[j];
      Nodo* nodo1 = arista_final->nodo1;
      Nodo* nodo2 = arista_final->nodo2;
      fprintf(output_file, "%d %d %d %d\n", nodo1->x, nodo1->y, nodo2->x, nodo2->y);
    }
    // for (int t = 0; t < cant_nodos; t++)
    // {
    //   int contador = 0;
    //   for (int k = 0; k < cant_nodos; k++)
    //   {
    //     Nodo* nodo = nodos[k];
    //     if (nodo->aristas == t)
    //     {
    //       contador += 1;
    //     }
    //   }
    //   printf(" %d nodos tienen %d aristas \n", contador, t);
    // }

    //libero
    for (int i = 0; i < cant_aristas; i++)
    {
      Arista* arista = aristas[i];
      arista_destroy(arista);
    }
    free(aristas);
    free(aristas_finales);
    for (int j = 0; j < cant_nodos; j++)
    {
      Nodo* nodo = nodos[j];
      nodo_destroy(nodo);
    }
    free(nodos);

    return 0;
}