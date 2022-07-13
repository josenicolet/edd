#include "item.h"

Item* item_init(int id, int peso)
{ 
    //necesito memoria
    Item* item = malloc(sizeof(Item));
    // cambio los valores
    *item = (Item){
        .id = id,
        .peso = peso,
        .next = NULL,
    };

    // se retorna la arista
    return item;

}

void agregar_item(Item* item, Item* nuevo)
{
    //agrego item a la lista de items de un agente
    //quiero ir al final de la lista y ac¿gregarlo ahi
    // vamos al final de la fila
    Item *last = item;
    while (last->next)
    {
        last = last->next;
    }
    // Lo agregamos como el nodo siguiente al ultimo nodo de la lista
    last->next = nuevo;
}

void imprimo_items(Item* item, FILE* output)
{
    //imprimo el item
    fprintf(output, "%d", item->id);
    //si el item tiene siguiente llamo recursivamente
    if (item->next)
    {
        //si tiene item siguiente
        fprintf(output, " ");
        imprimo_items(item->next, output);
    }
}

int partition(Item** items, int inicio, int final)
{
    //
    //entrega la posicion del pivote
    int pivote = (rand() % (final - inicio + 1)) + inicio;
    //printf("de inicio %i a final %i, eligo el pivote %i \n", inicio,final,pivote);
    //ver cunatos serian menores o mayores, y despues agregarlo oara poder crear las listas
    Item* item_pivote =  items[pivote];
    //printf("vaor pivote %lf \n", valor_pivote);
    int cant_menores = 0;
    int cant_mayores = 0;
    for (int i = inicio; i <= final; i++) //talvez es menor o igual
    {
        Item* item = items[i];
        if (item->peso < item_pivote->peso)
        {
            cant_menores += 1;
        }
        else if ((item->peso >= item_pivote->peso) && (i != pivote))
        {
            //es amyor o igul pero no mi pivote
            cant_mayores += 1;
        }
    }
    //creo los arreglos
    Item* menores[cant_menores];
    Item* mayores[cant_mayores];
    int contador_menores = 0;
    int contador_mayores = 0;
    //printf("hay %i menores y %i mayores \n", cant_menores, cant_mayores);
    for (int i = inicio; i <= final; i++) //talvez es menor o igual
    {
        //si es menor o mayor donde lo agrego
        Item* item = items[i];
        if (item->peso < item_pivote->peso)
        {
            menores[contador_menores] = item;
            contador_menores += 1;
        }
        else if ((item->peso >= item_pivote->peso) && (i != pivote))
        {
            //no es mi pivote
            mayores[contador_mayores] = item;
            contador_mayores += 1;
        }
        //printf("valors media %lf ", valor_media);
    }
    //printf("\n");
    // estan agregados a los arreglos
    //cambiar arreglo
    int contador = 0;
    for (int i = inicio; i <= final; i++) //talvez es menorr o igual
    {
        if (contador < cant_mayores)
        {
            //meto los menores
            items[i] = mayores[contador];
            contador += 1;
        }
        else if (contador == cant_mayores)
        {
            //si es la posicion de mi pivotre
            items[i] = item_pivote;
            contador += 1;
        }
        else if (contador > cant_mayores)
        {
            //meto los mayores
            items[i] = menores[contador - cant_mayores - 1];
            contador += 1;
        }
    }
    return (inicio + cant_mayores);
}

void quicksort(Item** items, int inicio, int final)
{
    if (inicio <= final)
    {
        //si esta vacio terminina
        //me entrega pposicion del pivote
        int pivote_partition = partition(items, inicio, final);
        quicksort(items, inicio, pivote_partition - 1);
        quicksort(items, pivote_partition + 1, final);

    }
}

void item_destroy(Item* item)
{
    // Si hay un nodo en la sig posicion, llamamos recursivamente a la funcion
    if (item->next)
    {
        // hacemos que se destruya el siguiente elemento en la lista ligada
        item_destroy(item->next);
    }
    // como destruimos la lista tambien tenemos que 
    // Luego, liberamos la lista
    free(item);
}