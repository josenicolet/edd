#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulation.h"
#include "../visualizer/visualizer.h"
#include "caja.h"

int main(int argc, char **argv)
{
  // Por defecto se abre la ventana
  bool visualize = true;
  if (argc == 4 && !strcmp(argv[3], "--novis"))
  {
    visualize = false;
  }
  else if (argc < 3 || argc >= 4)
  {
    printf("Modo de uso: %s INPUT OUTPUT [--novis]\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta al archivo de input que describe la escena\n");
    printf("\tOUTPUT es la ruta al archivo en donde se reportarán las colisiones\n");
    printf("\tEl flag opcional --novis indica que no se debe abrir la visualización del programa\n");
    // Exit code 1: Programa llamado sin todos los argumentos
    return 1;
  }

  // Inicializa los elementos de la simulación, y abre la ventana si visualize es true
  Simulation *sim = simulation_init_from_file(argv[1], visualize);

  // El archivo donde iremos reportando las colisiones
  FILE *output_file = fopen(argv[2], "w");

  // Para cada frame
  for (int f = 0; f < sim->frames; f++)
  {
    // Para cada particula
    for (int p = 0; p < sim->particle_count; p++)
    {
      // Inicialmente, esta particula no ha chocado con ningun segmento
      sim->particles[p].intersected_segment = NULL;
      // Por cada segmento
      // TODO: No revisar todos los segmentos, usar BVH para descartar los que estén muy lejos
      // ##########################################################################
      // tengo una particula p que quiero ver si choca
      Particle particula = sim->particles[p];
      //printf("particula con id %d en el frame %d \n", particula.ID, f);
      //la particula tinene un body (circulo) y circulo tienen center y radio
      //veo los limites del circulo
      double x_min_particula = particula.body.center.x - particula.body.radius;
      double x_max_particula = particula.body.center.x + particula.body.radius;
      double y_min_particula = particula.body.center.y - particula.body.radius;
      double y_max_particula = particula.body.center.y + particula.body.radius;
      //printf("particula con centro en (%lf, %lf), y radio %lf \n", particula.body.center.x, particula.body.center.y, particula.body.radius);
      Caja* caja_raiz = sim->caja_raiz;
      char eje = 'x';
      //llamo a la funcioni que revisa mi particula y cambia sus intersecciones
      //retorna el segmento cn el cual colisiona
      colisiona(caja_raiz, &sim->particles[p], x_min_particula, x_max_particula, y_min_particula, y_max_particula, eje);
      // if (sim->particles[p].intersected_segment == NULL)
      // {
      //   printf("\n");
      // }
      // else
      // {
      //   printf("la particula con id %i choco en el frame %d con el segmento %i \n", sim->particles[p].ID, f, sim->particles[p].intersected_segment->ID);
      // }
      // //llamo a la funcion que me devuelve la caja final de colisiones
      // Caja* caja_final = colision(caja_raiz, particula, x_min_particula, x_max_particula, y_min_particula, y_max_particula, eje);
      // //si no hay caja es porque no colisiona
      // if (!caja_final)
      // {
      //   //printf("no hay caja\n");
      // }
      // else
      // {
      //   //printf("colisiona\n");
      //   //si hay caja es porque colisiona
      //   int cant_seg_caja = caja_final->cant_segments;
      //   //por caja segmento en la caja veo si colisiona
      //   printf("mi caja tiene %i segmentos\n", cant_seg_caja);
      //   for (int s = 0; s < cant_seg_caja; s++)
      //   {
      //     Segment segmento = caja_final->segmentos[s];
      //     printf("estoy en el segmento %d \n",  segmento.ID);
      //     if (particle_segment_collision(particula, segmento))
      //     {
      //       printf("choco con el segmento\n");
      //       // Si es que no ha chocado con nada, o si no desempatamos por ID
      //       if (!sim->particles[p].intersected_segment || sim->segments[s].ID < sim->particles[p].intersected_segment->ID)
      //       {
      //         sim->particles[p].intersected_segment = &sim->segments[s];
      //       }
      //     }
      //   }
      // }
      //############################################################################
      // for (int s = 0; s < sim->segment_count; s++)
      // {
      //   // Si la particula choca con el segmento
      //   if (particle_segment_collision(sim->particles[p], sim->segments[s]))
      //   {
      //     // Si es que no ha chocado con nada, o si no desempatamos por ID
      //     if (!sim->particles[p].intersected_segment || sim->segments[s].ID < sim->particles[p].intersected_segment->ID)
      //     {
      //       sim->particles[p].intersected_segment = &sim->segments[s];
      //     }
      //   }
      // }
      //##############################################################
      // Si hubo intersección
      //printf(" es este %i y tengo este %i\n",sim->particles[p].ID, particula.ID);
      if (sim->particles[p].intersected_segment)
      {
        // Desviamos la partícula según el segmento con el que chocó
        particle_bounce_against_segment(&sim->particles[p], *sim->particles[p].intersected_segment);
        // Reportamos la colisión en el archivo de output
        fprintf(output_file, "%d %d %d\n", f, sim->particles[p].ID, sim->particles[p].intersected_segment->ID);
      }
      // Finalmente, la particula avanza
      particle_move(&sim->particles[p]);
    }
    // Si la ventana está abierta, dibujar las particulas en sus nuevas posiciones
    visualizer_draw_particles(sim->particles, sim->particle_count);
  }
  // Hace free de todo lo que se creo en simulation_init. Cierra la ventana.
  simulation_destroy(sim);

  fclose(output_file);

  return 0;
}
