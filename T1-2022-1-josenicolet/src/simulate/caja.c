#include "caja.h"

Caja* caja_init(double x_1, double x_2, double y_1, double y_2, int cant_segments)
{ 
    //necesito memoria
    Caja* caja= malloc(sizeof(Caja));
    // cambio los valores
    *caja = (Caja){
        .hijo_izq = NULL,
        .hijo_der = NULL,
        .padre = NULL,
        .nivel = 0,
        .x_1 = x_1,
        .x_2 = x_2,
        .y_1 = y_1,
        .y_2 = y_2,
        .cant_segments = cant_segments,
        .mediana =0,
        .segmentos = calloc(cant_segments, sizeof(Segment)),
    };

    // se retorna el nodo
    return caja;

}

int partition(double* medias_segmentos, int inicio, int final)
{
    //entrega la posicion del pivote
    int pivote = (rand() % (final - inicio + 1)) + inicio;
    //printf("de inicio %i a final %i, eligo el pivote %i \n", inicio,final,pivote);
    //ver cunatos serian menores o mayores, y despues agregarlo oara poder crear las listas
    double valor_pivote =  medias_segmentos[pivote];
    //printf("vaor pivote %lf \n", valor_pivote);
    int cant_menores = 0;
    int cant_mayores = 0;
    for (int i = inicio; i <= final; i++) //talvez es menor o igual
    {
        double valor_media = medias_segmentos[i];
        if (valor_media < valor_pivote)
        {
            cant_menores += 1;
        }
        else if ((valor_media >= valor_pivote) && (i != pivote))
        {
            //es amyor o igul pero no mi pivote
            cant_mayores += 1;
        }
    }
    //creo los arreglos
    double menores[cant_menores];
    double mayores[cant_mayores];
    int contador_menores = 0;
    int contador_mayores = 0;
    //printf("hay %i menores y %i mayores \n", cant_menores, cant_mayores);
    for (int i = inicio; i <= final; i++) //talvez es menor o igual
    {
        //si es menor o mayor donde lo agrego
        double valor_media = medias_segmentos[i];
        if (valor_media < valor_pivote)
        {
            menores[contador_menores] = valor_media;
            contador_menores += 1;
        }
        else if ((valor_media >= valor_pivote) && (i != pivote))
        {
            //no es mi pivote
            mayores[contador_mayores] = valor_media;
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
            medias_segmentos[i] = menores[contador];
            contador += 1;
        }
        else if (contador == cant_menores)
        {
            //si es la posicion de mi pivotre
            medias_segmentos[i] = valor_pivote;
            contador += 1;
        }
        else if (contador > cant_menores)
        {
            //meto los mayores
            medias_segmentos[i] = mayores[contador - cant_menores - 1];
            contador += 1;
        }
    }
    return (inicio + cant_menores);
}

int buscar_mediana(Caja* caja_raiz, double* medias_segmentos)
{
    //por cada media se segmento
    int mediana;
    int inicio = 0;
    int final = caja_raiz->cant_segments - 1;
    //posicion del pivote
    int pivote = partition(medias_segmentos, inicio, final);
    // si n es impar, la mediana es n/2 parte entera
    // si n es par diermos que la mediana es la division en 2
    int mitad = (int) caja_raiz->cant_segments / 2;
    while (pivote != mitad)
    {
        //mientras el pivoe no sea la mitad
        if (pivote < mitad)
        {
            //mientras el pivote sea más chico, la mitad está en el lado mayor
            inicio = pivote + 1; //parto desde la posicion seguiente del pivote
        }
        else
        {
            //la mitad está en el lado menor
            final = pivote - 1;
        }
        pivote = partition(medias_segmentos, inicio, final);
    }
    mediana = (int) medias_segmentos[pivote];
    return (mediana);
}

// segmentar caja
void segmentar_caja(Caja* caja_raiz, char eje)
{
    // busco la media
    //medias de segmentos
    double medias_segmentos[caja_raiz->cant_segments];
    //printf("cantidad de medias %i \n", caja_raiz->cant_segments);
    for (int i = 0; i < caja_raiz->cant_segments; i++)
    {
        //por cada segmento busco su media
        Segment segmento = caja_raiz->segmentos[i];
        //media de puntos
        double inicial;
        double final;
        if (eje == 'x')
        {
            inicial = segmento.pi.x;
            final = segmento.pf.x;
        }
        else if (eje == 'y')
        {
            inicial = segmento.pi.y;
            final = segmento.pf.y;
        }
        //printf("mi inicial es %lf y mi final es %lf ", inicial, final);
        double media_segmento = (int) (inicial + final) / 2;
        //printf("con su media %lf \n", media_segmento);
        medias_segmentos[i] = media_segmento;
    }
    int mediana = buscar_mediana(caja_raiz, medias_segmentos);
    //printf("mi mediana es %lf \n", mediana);
    caja_raiz->mediana = mediana;
    //con la mediana veo donde corto
    //pueden haber mas de uno en la mitad
    //por cada segmento en la caja veo las posiciones
    int cant_lado1 = 0;
    int cant_lado2 = 0;
    for (int i = 0; i < caja_raiz->cant_segments; i++)
    {
        //por cada segmento busco su media
        Segment segmento = caja_raiz->segmentos[i];
        //necesito saber a que lado va a ir y lo meto a un array
        //pero como no se de cuantos será calculo primero
        if (eje == 'x')
        {
            //si reviso el eje x
            if (segmento.pi.x < mediana && segmento.pf.x < mediana)
            {
                //si esta completamente antes de la mediana
                cant_lado1 += 1;
            }
            else if (segmento.pi.x > mediana && segmento.pf.x > mediana)
            {
                // esta completamente despues de la mediana
                cant_lado2 += 1;
            }
            else // if ((segmento.pi.x < mediana && segmento.pf.x > mediana) || (segmento.pi.x > mediana && segmento.pf.x < mediana))
            {
                //esta al medio
                cant_lado1 += 1;
                cant_lado2 += 1;
            }
        }
        else if (eje == 'y')
        {
            //si reviso el eje y
            if (segmento.pi.y < mediana && segmento.pf.y < mediana)
            {
                //si esta completamente antes de la mediana
                cant_lado1 += 1;
            }
            else if (segmento.pi.y > mediana && segmento.pf.y > mediana)
            {
                // esta completamente despues de la mediana
                cant_lado2 += 1;
            }
            else// if ((segmento.pi.y < mediana && segmento.pf.y > mediana) || (segmento.pi.y > mediana && segmento.pf.y < mediana))
            {
                //esta al medio
                cant_lado1 += 1;
                cant_lado2 += 1;
            }
        }
    }
    // ya tengo la cantidad de segmentos a cada lado
    //creo arreglos
    Segment segmentos_lado_1[cant_lado1];
    Segment segmentos_lado_2[cant_lado2];
    int contador_lado1 = 0;
    int contador_lado2 = 0;
    for (int i = 0; i < caja_raiz->cant_segments; i++)
    {
        //por cada segmento busco su media
        Segment segmento = caja_raiz->segmentos[i];
        //necesito saber a que lado va a ir y lo meto a un array
        if (eje == 'x')
        {
            //si reviso el eje x
            if (segmento.pi.x < mediana && segmento.pf.x < mediana)
            {
                //si esta completamente antes de la mediana
                segmentos_lado_1[contador_lado1] = segmento;
                contador_lado1 += 1;
                //printf("es completamente menor a la mediana\n");
            }
            else if (segmento.pi.x > mediana && segmento.pf.x > mediana)
            {
                // esta completamente despues de la mediana
                segmentos_lado_2[contador_lado2] = segmento;
                contador_lado2 += 1;
                //printf("es completamente mayor a la mediana \n");
            }
            else// if ((segmento.pi.x < mediana && segmento.pf.x > mediana) || (segmento.pi.x > mediana && segmento.pf.x < mediana))
            {
                //esta al medio
                segmentos_lado_1[contador_lado1] = segmento;
                segmentos_lado_2[contador_lado2] = segmento;
                contador_lado1 += 1;
                contador_lado2 += 1;
                //printf("esta al medio de la mediana \n");
            }
        }
        if (eje == 'y')
        {
            //si reviso el eje x
            if (segmento.pi.y < mediana && segmento.pf.y < mediana)
            {
                //si esta completamente antes de la mediana
                segmentos_lado_1[contador_lado1] = segmento;
                contador_lado1 += 1;
            }
            else if (segmento.pi.y > mediana && segmento.pf.y > mediana)
            {
                // esta completamente despues de la mediana
                segmentos_lado_2[contador_lado2] = segmento;
                contador_lado2 += 1;
            }
            else// if ((segmento.pi.y < mediana && segmento.pf.y > mediana) || (segmento.pi.y > mediana && segmento.pf.y < mediana))
            {
                //esta al medio
                segmentos_lado_1[contador_lado1] = segmento;
                segmentos_lado_2[contador_lado2] = segmento;
                contador_lado1 += 1;
                contador_lado2 += 1;
            }
        }
    }
    //los meti a la lista
    //si no estan vacias
    //consigo las medidas en de la cajas
    //inicializo las dos cajas
    Caja* caja_menor = NULL;
    Caja* caja_mayor = NULL;
    double medidas_1[4] = {0,0,0,0};
    double medidas_2[4] = {0,0,0,0};
    //printf("tengo %i al lado menor y %i al lado myor, con un total de %i segmentos \n", cant_lado1, cant_lado2, caja_raiz->cant_segments);
    if (cant_lado1 > 0)
    {
        //printf("tengo %i segmentos en chica \n", cant_lado1);
        medidas(segmentos_lado_1, cant_lado1, medidas_1);
        caja_menor = caja_init(medidas_1[0], medidas_1[1], medidas_1[2], medidas_1[3], cant_lado1);
        caja_menor->padre = caja_raiz;
        caja_raiz->hijo_izq = caja_menor;
    }
    if (cant_lado2 > 0)
    {
        //printf("tengo %i segmentos en grande \n", cant_lado2);
        medidas(segmentos_lado_2, cant_lado2, medidas_2);
        caja_mayor = caja_init(medidas_2[0], medidas_2[1], medidas_2[2], medidas_2[3], cant_lado2);
        caja_mayor->padre = caja_raiz;
        caja_raiz->hijo_der = caja_mayor;
    }
    //inicializo sus degmentos
    for (int i = 0; i < cant_lado1; i++)
    {
        Segment segmento = segmentos_lado_1[i];
        caja_menor->segmentos[i] = segmento;
    }
    //printf("el lado chico tinene %i cant y %i\n", cant_lado1, caja_menor->cant_segments);
    //printf("el lado grande tinene %i cant y %i\n", cant_lado2, caja_mayor->cant_segments);
    for (int j = 0; j < cant_lado2; j++)
    {
        Segment segmento = segmentos_lado_2[j];
        caja_mayor->segmentos[j] = segmento;
    }
    //pongo como hijo o padres
    //si estan vacios le pongo un NULL
}

//buscar medidas de una caja
void medidas(Segment* segmentos, int cant_segmentos, double* medidas)
{
    //printf("calculo medidad de caja para %i can de segmentos\n", cant_segmentos);
    //le entrego un arreglo de segmentos y devuelgo un arreglo de sus limites
    // tipo A[x_menor, x_mayor, y_menor, y_mayor]
    double x_min = 100000;
    double x_max = -100000;
    double y_min = 100000;
    double y_max = -100000;
    for (int i = 0; i < cant_segmentos; i++)
    {
        //printf("voy en %i \n ", i);
        //por cada segmento
        Segment segment = segmentos[i];
        if (segment.pi.x < x_min)
        {
            x_min = segment.pi.x;
        }
        if (segment.pf.x < x_min)
        {
            x_min = segment.pf.x;
        }
        if (segment.pi.x > x_max)
        {
            x_max = segment.pi.x;
        }
        if (segment.pf.x > x_max)
        {
            x_max = segment.pf.x;
        }
        if (segment.pi.y < y_min)
        {
            y_min = segment.pi.y;
        }
        if (segment.pf.y < y_min)
        {
            y_min = segment.pf.y;
        }
        if (segment.pi.y > y_max)
        {
            y_max = segment.pi.y;
        }
        if (segment.pf.y > y_max)
        {
            y_max = segment.pf.y;
        }
    }
    medidas[0] = x_min;
    medidas[1] = x_max;
    medidas[2] = y_min;
    medidas[3] = y_max;
    //printf("con xmin %lf, xmax %lf, ymin %lf, ymax %lf \n", x_min, x_max, y_min, y_max);
}

//segmentar cajas
void crea_arbol(Caja* caja_raiz, char eje)
{
    //me dan un arbol y lo segmento
    //mientras la caja no tenga 2 segmentos
    //printf("segmento segment con %i segments \n ", caja_raiz->cant_segments);
    segmentar_caja(caja_raiz, eje);
    //printf("me segmento \n");
    char nuevo_eje;
    if (eje == 'x')
    {
        nuevo_eje = 'y';
    }
    else
    {
        nuevo_eje = 'x';
    }
    //segmento el hioj izquierod
    if (caja_raiz->hijo_izq != NULL)
    {
        //si tinee hijo izquierdo
        //printf("tengo hijo izqu\n");
        if (caja_raiz->hijo_izq->cant_segments > 2)
        {
            if (caja_raiz->hijo_izq->cant_segments != caja_raiz->cant_segments)
            {
                //si no entra en un loop infinito
                //si tinee más de dos segmentos lo sigo segmentando
                //printf("segmento mi hijo izq\n");
                crea_arbol(caja_raiz->hijo_izq, nuevo_eje);
            }
        }
    }
    //segmento el hijo derecho
    if (caja_raiz->hijo_der != NULL)
    {
        //si tinee hijo derecho

        if (caja_raiz->hijo_der->cant_segments > 2)
        {
            if (caja_raiz->hijo_der->cant_segments != caja_raiz->cant_segments)
            {
                //si no entra a un loop infinito
                //si tinee más de dos segmentos lo sigo segmentando
                //printf("segmento mi hijo derecho\n");
                crea_arbol(caja_raiz->hijo_der, nuevo_eje);
            }
        }
    }
}

//revisar si la particula colisiona
Caja* colision(Caja* caja_raiz, Particle particula, double x_min, double x_max, double y_min, double y_max, char eje)
{
    Caja* caja_final;
    //reviso si colisiona con la caja raiz 
    //convierto mis min y max en las esquinas
    Vector sup_izq;
    Vector inf_der;
    sup_izq.x = caja_raiz->x_1;
    sup_izq.y = caja_raiz->y_2;
    inf_der.x = caja_raiz->x_2;
    inf_der.y = caja_raiz->y_1;
    //vectores definido
    Vector inf_izq;
    Vector sup_der;
    inf_izq.x = caja_raiz->x_1;
    inf_izq.y = caja_raiz->y_1;
    sup_der.x = caja_raiz->x_2;
    sup_der.y = caja_raiz->y_2;
    BoundingBox caja;
    // caja.min_point = sup_izq;
    // caja.max_point = inf_der;
    caja.min_point = inf_izq;
    caja.max_point = sup_der;
    //bounding box hecha
    //printf(" caja x_min %lf, xmax %lf, ymin %lf, ymax %lf \n", sup_izq.x, inf_der.x, inf_der.y , sup_izq.y);
    //printf("particula x_min %lf, xmax %lf, ymin %lf, ymax %lf \n", x_min, x_max, y_min , y_max);
    bool colisiona = particle_boundingbox_collision(particula, caja);
    if (colisiona)
    {
        //printf("colisiona con caja \n");
        if (caja_raiz->cant_segments < 1000)
        {
            //printf("con los segmentos [");
            for(int j = 0; j <caja_raiz->cant_segments; j++)
            {
                Segment seg = caja_raiz->segmentos[j];
                //printf("%i,",seg.ID);
            }
            //printf("]\n");
        }
    }
    else
    {
        //printf("no colisiona con caja \n ");
    }
    if (colisiona == false)
    {
        //si no colisiona
        caja_final = NULL;
    }
    else
    {
        //esta en esa caja
        if (!caja_raiz->hijo_der && !caja_raiz->hijo_izq)
        {
            //si la caja no tiene hijos es porque no se segmento más
            //como saco la mediana de los datos, siempre habran dos hijos
            caja_final = caja_raiz;
            //me devuelvo a mi
        }
        else
        {
            //llamo denuevo a la funcion dependiendo donde esté
            //veo donde esta
            //que eje
            char eje_nuevo;
            if (eje == 'x')
            {
                eje_nuevo = 'y';
            }
            else
            {
                eje_nuevo = 'x';
            }
            Caja* hijo_llamar = NULL;
            if (eje == 'x')
            {

                //me importa el eje x
                if (x_max < caja_raiz->mediana)
                {
                    //printf("el izq\n");
                    //esta completaente en el lado izquierdo
                    hijo_llamar = caja_raiz->hijo_izq;
                }
                else if (x_min > caja_raiz->mediana)
                {
                    //printf("el der\n");
                    //esta completamente en el lado derecho
                    hijo_llamar = caja_raiz->hijo_der;
                }
                else
                {
                    //printf("queda al medio\n");
                    hijo_llamar = caja_raiz->hijo_izq;
                    // //esta al medio los dos lo abarcan
                    // printf("esta al medio\n");
                    // if (caja_raiz->hijo_izq->x_2 > x_max)
                    // {
                    //     //lo abarca 
                    //     printf("lo abarca el hijo iz\n");
                    //     hijo_llamar = caja_raiz->hijo_izq;
                    // }
                    // else if (caja_raiz->hijo_der->x_1 < x_min)
                    // {
                    //     //si no lo abarca el otro este si
                    //     printf("lo abarca el hijo der\n");
                    //     hijo_llamar = caja_raiz->hijo_der;
                    // }
                    // else
                    // {
                    //     //esta en la mitad mitas
                    //     printf("no lo abarcan completo\n");
                    //     //depende donde este el centro?
                    //     if (particula.body.center.x < caja_raiz->hijo_izq->x_2)
                    //     {
                    //         //si el centro esta a la izquierda
                    //         hijo_llamar = caja_raiz->hijo_izq;
                    //     }
                    //     else
                    //     {
                    //         hijo_llamar = caja_raiz->hijo_der;
                    //     }
                    // }
                }
            }
            else if (eje == 'y')
            {
                //me importa el eje x
                if (y_max < caja_raiz->mediana)
                {
                    //esta completaente en el lado izquierdo
                    //printf("lo abarca el izq\n");
                    hijo_llamar = caja_raiz->hijo_izq;
                }
                else if (y_min > caja_raiz->mediana)
                {
                    //esta completamente en el lado derecho
                    //printf("lo abarca el der\n");
                    hijo_llamar = caja_raiz->hijo_der;
                }
                else
                {
                    hijo_llamar = caja_raiz->hijo_izq;
                    // printf("esta al medio\n");
                    // //esta al medio los dos lo abarcan
                    // if (caja_raiz->hijo_izq->y_2 > y_max)
                    // {
                    //     //lo abarca 
                    //     hijo_llamar = caja_raiz->hijo_izq;
                    // }
                    // else if (caja_raiz->hijo_der->y_1 < y_min)
                    // {
                    //     //si no lo abarca el otro este si
                    //     printf("lo abarca el hijo der\n");
                    //     hijo_llamar = caja_raiz->hijo_der;
                    // }
                    // else
                    // {
                    //     //esta en la mitad mitas
                    //     printf("no lo abarcan completo\n");
                    //     //depende donde este el centro?
                    //     if (particula.body.center.y < caja_raiz->hijo_izq->y_2)
                    //     {
                    //         //si el centro esta a la izquierda
                    //         hijo_llamar = caja_raiz->hijo_izq;
                    //     }
                    //     else
                    //     {
                    //         hijo_llamar = caja_raiz->hijo_der;
                    //     }
                    // }
                }
            }
            //tengo a que hijo llamar
            //llamo a la funcion denuevo con su hijo
            caja_final = colision(hijo_llamar, particula, x_min, x_max, y_min, y_max, eje_nuevo);
        }
    }
    return caja_final;
}

//retorna el segmento cn el cual colisiona
void colisiona(Caja* caja_raiz, Particle* particula, double x_min, double x_max, double y_min, double y_max, char eje)
{
    //veo si la particula está dentro de la caja
    //Particle particula1 = *particula;
    Vector sup_izq;
    Vector inf_der;
    sup_izq.x = caja_raiz->x_1;
    sup_izq.y = caja_raiz->y_2;
    inf_der.x = caja_raiz->x_2;
    inf_der.y = caja_raiz->y_1;
    //vectores definido
    //vectores definido
    Vector inf_izq;
    Vector sup_der;
    inf_izq.x = caja_raiz->x_1;
    inf_izq.y = caja_raiz->y_1;
    sup_der.x = caja_raiz->x_2;
    sup_der.y = caja_raiz->y_2;

    BoundingBox caja;
    // caja.min_point = sup_izq;
    // caja.max_point = inf_der;
    caja.min_point = inf_izq;
    caja.max_point = sup_der;
    // caja.max_point = inf_izq;
    // caja.min_point = sup_der;
    bool colisiona_caja = particle_boundingbox_collision(*particula, caja);
    //si no esta dentro de la caja
    //si colisona con la caja
    //printf(" caja x_min %lf, xmax %lf, ymin %lf, ymax %lf \n", sup_izq.x, inf_der.x, inf_der.y , sup_izq.y);
    //printf("particula x_min %lf, xmax %lf, ymin %lf, ymax %lf \n", x_min, x_max, y_min , y_max);
    if (colisiona_caja)
    {
        //printf("caja colisiona\n");
        //veo si tiene hijos, si tengo es porque segui segmentando
        if (!caja_raiz->hijo_izq && !caja_raiz->hijo_der)
        {
            //printf("no tiene mas hijos esta si o si en mi\n");
            //busco en mis segmentos
            for (int i = 0; i < caja_raiz->cant_segments; i++)
            {
                Segment* segmento = &caja_raiz->segmentos[i];
                //si mi segmento choca
                //rintf("segmento %i \n", segmento.ID);
                if (particle_segment_collision(*particula, *segmento))
                {
                    //printf("reealmente colisona con segmento %i\n", segmento.ID);
                    // Si es que no ha chocado con nada, o si no desempatamos por ID
                    if (particula->intersected_segment)
                    {
                        //printf("ya tiene %i \n", particula->intersected_segment->ID);
                    }
                    if (particula->intersected_segment == NULL || segmento->ID < particula->intersected_segment->ID)
                    {
                        //printf("guardo colision\n");
                        particula->intersected_segment = segmento;
                        //printf("ahora tengo a %i \n", segmento->ID);

                    }
                }
            }
        }
        //tiene hijos
        else
        {
            //busco si es menor o mayor a la media y lo llamo con ese hijo
            //veo mi nuevo eje
            char eje_nuevo;
            if (eje == 'x')
            {
                eje_nuevo = 'y';
            }
            else
            {
                eje_nuevo = 'x';
            }
            if (eje == 'x')
            {

                //me importa el eje x
                if (caja_raiz->hijo_izq != NULL && x_max < caja_raiz->mediana)
                {
                    //esta completaente en el lado izquierdo
                    //llamo a la funcion con el hijo izquierdo
                    //printf("llamoa hijo izquierdo\n");
                    colisiona(caja_raiz->hijo_izq, particula, x_min, x_max, y_min, y_max, eje_nuevo);
                }
                else if (caja_raiz->hijo_der != NULL && x_min > caja_raiz->mediana)
                {
                    //esta completamente en el lado derecho
                    //printf("llamoa hijo derecho\n");
                    colisiona(caja_raiz->hijo_der, particula, x_min, x_max, y_min, y_max, eje_nuevo);
                }
                else
                {
                    //printf("llamoa a los dos\n");
                    //esta al medio llamo a lo dos hijos
                    if (caja_raiz->hijo_izq != NULL)
                    {
                        colisiona(caja_raiz->hijo_izq, particula, x_min, x_max, y_min, y_max, eje_nuevo);
                    }
                    if (caja_raiz->hijo_der != NULL)
                    {
                        colisiona(caja_raiz->hijo_der, particula, x_min, x_max, y_min, y_max, eje_nuevo);
                    }
                }
            }
            else
            {
                //es el eje y
                if (caja_raiz->hijo_izq != NULL && y_max < caja_raiz->mediana)
                {
                    //printf("llamoa hijo izquierdo\n");
                    //esta completaente en el lado izquierdo
                    colisiona(caja_raiz->hijo_izq, particula, x_min, x_max, y_min, y_max, eje_nuevo);
                }
                else if (caja_raiz->hijo_der != NULL && y_min > caja_raiz->mediana)
                {
                    //printf("llamoa hijo derecho\n");
                    //esta completamente en el lado derecho
                    colisiona(caja_raiz->hijo_der, particula, x_min, x_max, y_min, y_max, eje_nuevo);
                }
                else
                {
                    //printf("llamoa los dos\n");
                    //esta al emdio, llamo a los dos hijo
                    if (caja_raiz->hijo_izq != NULL)
                    {
                        colisiona(caja_raiz->hijo_izq, particula, x_min, x_max, y_min, y_max, eje_nuevo);
                    }
                    if (caja_raiz->hijo_der != NULL)
                    {
                        colisiona(caja_raiz->hijo_der, particula, x_min, x_max, y_min, y_max, eje_nuevo);
                    }
                }
            }
        }
    }
}

// destruir
void caja_destroy(Caja* caja)
{
    //destruyo sus hijos primero
    //si tiene hijos destruyo los hijos
    if (caja->hijo_izq != NULL)
    {
        caja_destroy(caja->hijo_izq);
    }
    if (caja->hijo_der != NULL)
    {
        caja_destroy(caja->hijo_der);
    }
    free(caja->segmentos);
    free(caja);
}