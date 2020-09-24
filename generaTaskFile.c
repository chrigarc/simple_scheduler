#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
  // numeros aleatorios dif en cada ejecucion:
  srand(time(NULL));

  // Nombre del archivo a generar
  char *archivo = argv[1];

  // Ruta donde se encuentra el program
  char *ruta = argv[2];

  // nombre del archivo a ejecutar
  char *programa = argv[3];

  // Ruta donde se almacenera el resultado
  char *rutaSalida = argv[4];

  // Numero de repeticiones a ejecutar
  int repeticiones = atoi(argv[5]);

  FILE *out;
  out=fopen(archivo, "w");

  // aleatorio para el parametro del programa
  int aux_aleatorio;

  for(int i =0; i < repeticiones; i++) {
    // generamos aleatorios entre 100'000 y 10'000'000
    aux_aleatorio = 100000 + (rand() % 9900001);
    fprintf(out, "%s%s %d %ssalida%d.txt\n", 
      ruta, programa, aux_aleatorio, rutaSalida, (i+1));
  }

  fclose(out);

  return 0;
}