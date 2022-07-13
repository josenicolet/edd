#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void insertar_nodo(Nodo* padre, Nodo* nodo)
{
  //lo inserto en el lado que debe
  //tengo el padre y tengo que insertarlo en su hijo
  //ver que hijo
  if (nodo->valor < padre->valor)
  {
    //lo inserto a la izquierda
    padre->hijo_izq = nodo;
  }
  else if (nodo->valor > padre->valor)
  {
    //se inserta a la derecha
    padre->hijo_der = nodo;
  }
  else if (nodo->valor == padre->valor)
  {
    //lo hago por id
    if (nodo->id < padre->id)
    {
      //se va a la izq
      padre->hijo_izq = nodo;
    }
    else if (nodo->id > padre->id)
    {
      //se va a la derecha
      padre->hijo_der = nodo;
    }
  }
  nodo->padre = padre;
  nodo->nivel = padre->nivel + 1;
  
}

Nodo* buscar_nodo(Nodo* raiz, int valor, int id)
{
  Nodo* padre = NULL;
  //primero veo el valor y reviso si es menor o mayor
  if (valor < raiz->valor)
  {
    //se va al hijo izquierdo
    if (!raiz->hijo_izq)
    {
      //si no tiene hijo izquierdo
      //entrego el padre
      padre = raiz;

    }
    else 
    {
      //tiene hijo izquierdo, vuelvo a llamar a la funcion pero en mi hijo
      padre = buscar_nodo(raiz->hijo_izq, valor, id);
    }
  }
  else if (valor > raiz->valor)
  {
    //se va al hijo derecho
    if (!raiz->hijo_der)
    {
      //no tiene hijo derecho, devulevo el paadre
      padre = raiz;
    } 
    else
    {
      //tinee hijo derecho, llamo la funcion con el hijo
      padre = buscar_nodo(raiz->hijo_der, valor, id);
    }
  }
  else if (valor == raiz->valor)
  {
    //si tiene el mismo tengo que hacerlo por orden de id
    if (id < raiz->id)
    {
      //si debe ir antes
      if (!raiz->hijo_izq)
      {
        //si no tiene hijo izquierdo
        //lo inserto como hijo, entrego el padre
        padre = raiz;

      }
      else 
      {
        //tiene hijo izquierdo, vuelvo a llamar a la funcion pero en mi hijo
        padre = buscar_nodo(raiz->hijo_izq, valor, id);
      }

    }
    else if (id > raiz->id)
    {
      if (!raiz->hijo_der)
      {
        //no tiene hijo derecho, devulevo el paadre
        padre = raiz;
      } 
      else
      {
        //tinee hijo derecho, llamo la funcion con el hijo
        padre = buscar_nodo(raiz->hijo_der, valor, id);
      }
    }
  }
  return padre;
}

void path(Nodo* raiz, int valor, FILE* file)
{
    //buscar el path
    //caso base
    if (raiz->valor == valor)
    {
        //si es el que busco imprimo el numero
        fprintf(file, "%i\n", valor);
    }
    else
    {
        //imprimo al padre
        fprintf(file, "%i ", raiz->valor);
        //si no es igual busco sus hijos
        if (raiz->valor > valor)
        {
            // veo a la izquierda
            if (!raiz->hijo_izq)
            {
                //si no tiene hijo izq
                //el numero tendria que ir ahi, imprimo x
                fprintf(file, "X\n");
            }
            else if (raiz->hijo_izq)
            {
                //tiene hijo izquierdo
                //reviso con su hijo
                path(raiz->hijo_izq, valor, file);
            }
        }
        else if (raiz->valor < valor)
        {
            //me voy a ver a la derecha
            if (!raiz->hijo_der)
            {
                //si no tinee hijio derecho es donde deberia ir
                fprintf(file, "X\n");
            }
            else if (raiz->hijo_der)
            {
                //tiene hijo derechi reviso por ahí
                path(raiz->hijo_der, valor, file);
            }
        }
    }
}

void deep(Nodo* raiz, int valor, FILE* file)
{
    //busco el nodo
    //caso base es el que busco
    if (raiz->valor == valor)
    {
        //si es el que busco imprimo el numero
        fprintf(file, "%i\n", raiz->nivel);
    }
    else
    {
        //si no es el que busco tengo que buscar hacia abajo
        // como sabemos que el valor si está no es posible que su hijo sea nulo
        //porque osino no estaria el valor en el arbol
        if (raiz->valor > valor)
        {
            //voy a la izquierda
            //busco con el hijo izquierdo
            deep(raiz->hijo_izq, valor, file);
        }
        else if (raiz->valor < valor)
        {
            //busco en el hijo derecho
            deep(raiz->hijo_der, valor, file);
        }
    }
}

void orden(Nodo* raiz, FILE* file)
{
    //primero busco el nodo más chico
    if (raiz->hijo_izq)
    {
        //si en nodo tinee hijo izquierdo
        orden(raiz->hijo_izq, file);
    }
    //me impreimo a mi
    fprintf(file, "%i ", raiz->valor);
    if (raiz->hijo_der)
    {
        //si tengo hijo derecho
        orden(raiz->hijo_der, file);
    }
}

// int contar_subarbol(Nodo* raiz, int suma)
// {
//   if (raiz->hijo_izq)
//   {
//       //si en nodo tinee hijo izquierdo
//       suma = contar_subarbol(raiz->hijo_izq, suma);
//   }
//   //me impreimo a mi
//   suma += 1;
//   if (raiz->hijo_der)
//   {
//       //si tengo hijo derecho
//       suma = contar_subarbol(raiz->hijo_der, suma);
//   }
//   return suma;
// }

int contar_subarbol(Nodo* nodo, int suma)
{
    //caso base llego a una hoja
    if (!nodo->hijo_izq && !nodo->hijo_der)
    {
        //no tiene hijos
        //la destruyoo
        suma += 1;
    }
    else
    {
        //no es una hoja reviso sus hijos
        //reviso el hijo izquierdo
        if (nodo->hijo_izq)
        {
            //si tiene izo izquierdo
            suma = contar_subarbol(nodo->hijo_izq, suma);
        }
        //reviso el hijo derecho
        if (nodo->hijo_der)
        {
            //tiene hijo derecho
            suma = contar_subarbol(nodo->hijo_der, suma);
        }
        //sumo el del padre
        suma += 1;
    }
    return suma;
}

bool destroy(Nodo* raiz, int valor, FILE* file)
{
  bool devuelvo = false;
  //busco al nodo que quiero
  //caso base---lo encunetro
  //si existe nodo
  if (raiz->valor == valor)
  {
    // //dejo al papa sin hijo en el lado
    // if (raiz->padre)
    // {
    //   //si no es el nodo raiz
    //   if (raiz->padre->hijo_izq)
    //   {
    //     //si tiene hijo izquierdo
    //     if (raiz->padre->hijo_izq->valor == valor)
    //     {
    //       //si el hijo izquiero de mi padre es el valor que busco
    //       raiz->padre->hijo_izq = NULL;
    //     }
    //   }
    //   else if (raiz->padre->hijo_der)
    //   {
    //     //si tiene hijo derecho
    //     if (raiz->padre->hijo_der->valor == valor)
    //     {
    //       //si el hijo derecho de mi padre es el valor que busco
    //       raiz->padre->hijo_der = NULL;
    //     }
    //   }
    // }
    if (raiz->padre->valor < raiz->valor)
    {
      //soy hijo derecho
      raiz->padre->hijo_der = NULL;
    }
    else if (raiz->padre->valor > raiz->valor)
    {
      //soy hijo izquierdo
      raiz->padre->hijo_izq = NULL;
    }
    raiz->padre=NULL;
    //ahora el padre no tinee link y hay que destruir los nodos
    int cant_destruidos = contar_subarbol(raiz, 0);
    //imprimo la cantidad de nodos destruidos
    fprintf(file, "%i\n", cant_destruidos);
    return true;
  }
  else
  {
    //no soy yo, veo a mis hijos
    if (raiz->valor > valor)
    {
      //si tengo hijo izq
      if (raiz->hijo_izq)
      {
        //veo en el hijo izquierdo
        devuelvo = destroy(raiz->hijo_izq, valor, file);
      }
      //si es menor y no tengo hijo izquierd
    }
    else if (raiz->valor < valor)
    {
      if (raiz->hijo_der)
      {
        //busco en el hijo derecho
        devuelvo = destroy(raiz->hijo_der, valor, file);
      }
    }
  }
  
}
