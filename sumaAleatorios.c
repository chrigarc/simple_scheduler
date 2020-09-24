#include <stdlib.h> // rand()
#include <stdio.h> // files
#include <time.h> // time()

int *genera_vector(int n);
void actualiza_vector(int *vect, int n);
int suma_vector(int *vect, int n);
void escribe_archivo(FILE *, int res);
void libera_vector(int *vect);

int main(int argc, char **argv) {
  // numeros aleatorios dif en cada ejecucion:
  srand(time(NULL));

  // lectura de parametros:
  int num_rep = atoi(argv[1]);
  char *salida = argv[2];

  int n = 100; // tamanio del vector
  
  int *vect = genera_vector(n);

  FILE *out;
  out=fopen(salida, "w");

  for(int i =0; i < num_rep; i++) {    
    //actualiza_vector(vect, n);
    escribe_archivo(out, suma_vector(vect, n));
  }
  fclose(out);
  libera_vector(vect);
}

int *genera_vector(int n) {
  int *vect = malloc(sizeof(int)*n);
  for(int i =0; i < n; i++) {
    // genera numeros enteros en el rango [1, 10]
    vect[i] = 1 +  (rand() % 10);
  }
  return vect;
}

void actualiza_vector(int *vect, int n) {
  for(int i =0; i < n; i++) {
    // genera numeros enteros en el rango [1, 10]
    vect[i] = 1 +  (rand() % 10);
  }
}

int suma_vector(int *vect, int n) {
  int res = 0;

  for(int i =0; i < n; i++) {
    res += vect[i];
  }

  return res;
}

void escribe_archivo(FILE *out, int res) {
  fprintf(out, "%d\n", res);
}

void libera_vector(int *vect) {
  free(vect);
}