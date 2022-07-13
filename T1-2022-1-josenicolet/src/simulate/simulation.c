#include <stdio.h>
#include <stdlib.h>

#include "../visualizer/visualizer.h"
#include "simulation.h"
#include "caja.h"

/** Avisa que el archivo de input no era válido para este programa */
static void invalid_file()
{
  printf("Archivo de input inválido :(\n");
  exit(2);
}

/** Lee una simulación a partir de un archivo, y abre la interfaz gráfica para visualizarla
 * @param input_file ruta al archivo que describe la simulación
 * @param visualize indica si debe abrirse o no la interfaz gráfica
 * @returns objeto Simulation* que contiene los segmentos y partículas de la simulación
 */
Simulation* simulation_init_from_file(char* input_file, bool visualize)
{
  FILE* f = fopen(input_file, "r");  
  if(!f)
  {
    printf("Archivo no existe o no se puede leer: %s\n", input_file);
    exit(2);
  }

  Simulation* sim = malloc(sizeof(Simulation));

  fscanf(f, "%d", &sim->frames) ?: invalid_file();

  int height, width;
  fscanf(f, "%d %d", &height, &width) ?: invalid_file();

  double particle_radius;
  fscanf(f, "%d %lf", &sim -> particle_count, &particle_radius) ?: invalid_file();
  sim -> particles = calloc(sim -> particle_count, sizeof(Particle));

  if(visualize)
  {
    printf("Abriendo la ventana del visualizador...\n");
    printf("Si logro abrir la ventana, tu programa se caerá silenciosamente :/\n");
    printf("Si no se abre nada y estás en WSL, asegurate de tener abierto xserver y haber hecho export DISPLAY\n");
    printf("Si no quieres abrir la ventana, llama al programa con el flag --novis al final\n");
    visualizer_open(height, width, sim -> particle_count);
  }

  for(int i = 0; i < sim -> particle_count; i++)
  {
    Particle p;
    p.body.radius = particle_radius;
    p.ID = i;
    p.intersected_segment = NULL;
    fscanf(f, "%lf %lf %lf %lf", &p.body.center.x, &p.body.center.y, &p.velocity.x, &p.velocity.y) ?: invalid_file();
    sim -> particles[i] = p;
  }

  visualizer_draw_particles(sim->particles, sim->particle_count);

  fscanf(f, "%d", &sim -> segment_count) ?: invalid_file();
  sim -> segments = calloc(sim -> segment_count, sizeof(Segment));

  visualizer_set_color(1,1,1);

  for(int i = 0; i < sim->segment_count; i++)
  {
    Segment seg;
    seg.ID = i;
    fscanf(f, "%lf %lf %lf %lf", &seg.pi.x, &seg.pi.y, &seg.pf.x, &seg.pf.y) ?: invalid_file();
    sim->segments[i] = seg;
    visualizer_draw_segment(sim->segments[i]);
  }
  double medidas_raiz[4] = {0,0,0,0};
  medidas(sim->segments, sim->segment_count, medidas_raiz);
  
  // tengo las alturas de la primera caja
  //la inicializo y meto los segmentos
  Caja* caja_raiz = caja_init(medidas_raiz[0], medidas_raiz[1], medidas_raiz[2], medidas_raiz[3], sim->segment_count);
  for (int i = 0; i < sim->segment_count; i++)
  {
    //
    Segment segment = sim->segments[i];
    caja_raiz->segmentos[i] = segment;
  }
  //tengo la primera caja hecha, que inclye todos los segmentos
  sim->caja_raiz = caja_raiz;
  //cuando busco, busco primero en esta caja
  //segmento todo lo demas para despues poder buscar
  //creo el arbol
  crea_arbol(caja_raiz, 'x');
  //tengo el arbol creado y ahora para buscarlo en main

  


  fclose(f);

  return sim;
}

/** Libera todos los recursos asociados a la simulacion 
 * @param sim simulación construida por la función simulation_init_from_file()
 */
void   simulation_destroy(Simulation* sim)
{
  caja_destroy(sim->caja_raiz);
  free(sim->particles);
  free(sim->segments);
  free(sim);
  visualizer_close();
}

