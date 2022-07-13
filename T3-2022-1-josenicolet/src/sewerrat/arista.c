#include "arista.h"

Arista* arista_init(Nodo* nodo1, Nodo* nodo2, int distancia)
{ 
    //necesito memoria
    Arista* arista = malloc(sizeof(Arista));
    // cambio los valores
    *arista = (Arista){
        .nodo1 = nodo1,
        .nodo2 = nodo2,
        .distancia = distancia,
    };

    // se retorna la arista
    return arista;

}

int partition(Arista** aristas, int inicio, int final)
{
    //entrega la posicion del pivote
    int pivote = (rand() % (final - inicio + 1)) + inicio;
    //printf("de inicio %i a final %i, eligo el pivote %i \n", inicio,final,pivote);
    //ver cunatos serian menores o mayores, y despues agregarlo oara poder crear las listas
    Arista* arista_pivote =  aristas[pivote];
    //printf("vaor pivote %lf \n", valor_pivote);
    int cant_menores = 0;
    int cant_mayores = 0;
    for (int i = inicio; i <= final; i++) //talvez es menor o igual
    {
        Arista* arista = aristas[i];
        if (arista->distancia < arista_pivote->distancia)
        {
            cant_menores += 1;
        }
        else if ((arista->distancia >= arista_pivote->distancia) && (i != pivote))
        {
            //es amyor o igul pero no mi pivote
            cant_mayores += 1;
        }
    }
    //creo los arreglos
    Arista* menores[cant_menores];
    Arista* mayores[cant_mayores];
    int contador_menores = 0;
    int contador_mayores = 0;
    //printf("hay %i menores y %i mayores \n", cant_menores, cant_mayores);
    for (int i = inicio; i <= final; i++) //talvez es menor o igual
    {
        //si es menor o mayor donde lo agrego
        Arista* arista = aristas[i];
        if (arista->distancia < arista_pivote->distancia)
        {
            menores[contador_menores] = arista;
            contador_menores += 1;
        }
        else if ((arista->distancia >= arista_pivote->distancia) && (i != pivote))
        {
            //no es mi pivote
            mayores[contador_mayores] = arista;
            contador_mayores += 1;
        }
        //printf("valors media %lf ", valor_media);
    }
    //printf("\n");
    // estan agregados a los arreglos
    //cambiar arreglo
    int contador = 0;
    // printf("inicio %i y final %i \n", inicio, final);
    // printf("menores \n");
    // for (int i = 0; i < cant_menores; i++)
    // {
    //     printf("%lf ", menores[i]);
    // }
    // printf("mayores \n");
    // for (int j = 0; j < cant_mayores; j++)
    // {
    //     printf("%lf ", mayores[j]);
    // }
    for (int i = inicio; i <= final; i++) //talvez es menorr o igual
    {
        if (contador < cant_menores)
        {
            //meto los menores
            aristas[i] = menores[contador];
            contador += 1;
        }
        else if (contador == cant_menores)
        {
            //si es la posicion de mi pivotre
            aristas[i] = arista_pivote;
            contador += 1;
        }
        else if (contador > cant_menores)
        {
            //meto los mayores
            aristas[i] = mayores[contador - cant_menores - 1];
            contador += 1;
        }
    }
    return (inicio + cant_menores);
}

void quicksort(Arista** aristas, int inicio, int final)
{
    if (inicio <= final)
    {
        //si esta vacio terminina
        //me entrega pposicion del pivote
        int pivote_partition = partition(aristas, inicio, final);
        quicksort(aristas, inicio, pivote_partition - 1);
        quicksort(aristas, pivote_partition + 1, final);

    }
}

// destruir
void arista_destroy(Arista* arista)
{
    free(arista);
}