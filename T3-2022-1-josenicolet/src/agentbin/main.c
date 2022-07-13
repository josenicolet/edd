#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"
#include "agente.h"


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

int main(int argc, char **argv){
    
    check_arguments(argc, argv);

    // extraigo lo que necesito
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    //leemos
    int capacidad_agentes;
    fscanf(input_file, "%d", &capacidad_agentes);
    int cant_items;
    fscanf(input_file, "%d", &cant_items);
    Item** items = malloc(cant_items * sizeof(Item*));

    for (int i = 0; i < cant_items; i++)
    {
      //
      int peso;
      fscanf(input_file, "%d", &peso);
      Item* item = item_init(i, peso);
      items[i] = item;
    }
    //tengo todos los items en un areglo
    int inicio = 0;
    int final = cant_items - 1;
    quicksort(items, inicio, final);
    //arreglo lo dejo de mayor a menor

    int cant_agentes = 1;
    //primer agente con primer item
    Agente* agente = agente_init(0, items[0]);
    for (int i = 1; i < cant_items; i++)
    {
      //por cada item del areglo
      Item* item = items[i];
      //printf("item con id %d y peso %d\n", item->id, item->peso);
      //reviso si cabe en el primero
      bool cupo = cabe_item(item, agente, capacidad_agentes);
      //si cupo es true, cupo en los agentes ya hechos
      //si cupo es flase, se tuvo que crear un agente nuevo
      if (cupo == false)
      {
        cant_agentes += 1;
      }
    }
    //imprimo
    fprintf(output_file, "%d\n", cant_agentes);
    //imprimo lista ligada de agente, imprimiendo la lista ligada de loos itmes
    imprimir_agente(agente, output_file);

    //libero memoria
    agente_destroy(agente);
    free(items);

    
    return 0;
}