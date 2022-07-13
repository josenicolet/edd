#include <stdio.h>
#include <stdbool.h>

// Importamos la lista ligada
#include "lista_ligada.h"

int main(int argc, char** argv)
{

    // inicializamos una nueva lista

    List* list = list_init();

    // le agregamos 5 nodos

    for (int i = 0; i < 5; i++)
    {
        list_append(list, i);
    }

    printf("La lista inicial contiene:\n");
    list_print(list);

    list_append(list, 100);
    printf("Ahora le agregué un nodo más\n");
    list_print(list);

    // Ahora debemos liberar la memoria utilizada
    list_destroy(list);

    // fin del programa! :D
  return 0;
}