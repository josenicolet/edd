#include "agente.h"

Agente* agente_init(int id, Item* item)
{ 
    //necesito memoria
    Agente* agente = malloc(sizeof(agente));
    // cambio los valores
    *agente = (Agente){
        .id = id,
        .item = item,
        .next = NULL,
        .peso_actual = item->peso,
    };

    // se retorna la arista
    return agente;

}

bool cabe_item(Item* item, Agente* agente, int capacidad)
{
    //tengo la lista ligada de agentes y el item que quiero inserta
    //veo si cabe en este, si no cabe , hago llamado recursivo
    int queda = capacidad - agente->peso_actual;
    if (item->peso <= queda)
    {
        //el item cabe, lo agrego a la lisat ligada de items con funcion
        agregar_item(agente->item, item);
        agente->peso_actual += item->peso;
        return true;
    }
    //si cupo en el primero
    else
    {
        if (agente->next)
        {
            //no cupo, reviso los siguientes (tiene siguiente)
            bool cabe = cabe_item(item, agente->next, capacidad);
            return cabe;
        }
        else
        {
            //no cupo yh no tiene mas agentes creo uno
            Agente* agente_nuevo = agente_init(agente->id + 1, item);
            agente->next = agente_nuevo;
            return false;
        }
    }
}

void imprimir_agente(Agente* agente, FILE* output)
{
    //lo imprimo
    //nueva linea con los id de los items
    imprimo_items(agente->item, output);
    fprintf(output, "\n");
    //fprintf(output, "\n peso actual= %d \n", agente->peso_actual);
    //si hay siguiente llamo recursivamente con la sigueinte
    if (agente->next)
    {
        //si hay un siguiente agente
        imprimir_agente(agente->next, output);
    }
}

void agente_destroy(Agente* agente)
{
    // Si hay un nodo en la sig posicion, llamamos recursivamente a la funcion
    if (agente->next)
    {
        // hacemos que se destruya el siguiente elemento en la lista ligada
        agente_destroy(agente->next);
    }
    // como destruimos la lista tambien tenemos que 
    if (agente) // el puntero no apunta a NULL
    {
        if (agente->item)
        {
            //hay pasajeros en la fila
            Item *item = agente->item;
            item_destroy(item);
        }
    }
    // Luego, liberamos la lista
    free(agente);
}