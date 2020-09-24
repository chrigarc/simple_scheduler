#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
 
int main(int argc, char **argv) {

  char *machinesFile = argv[1];
  char *tasksFile = argv[2];

  int totalRecursos = atoi(argv[3]);
  int totalTareas = atoi(argv[4]);

  FILE *fTasks, *fMachines; //Variables para manejo de archivos

  fTasks = fopen(tasksFile, "r"); //Abre para lectura
  fMachines = fopen(machinesFile, "r"); //Abre para lectura


  size_t bufsize = 200;
  char tareaActual[bufsize];
  char *buffer = tareaActual; 

  // Init lista de recursos disponibles
  char *machines[totalRecursos];
  int lista_recursos[totalRecursos];
  // printf("Leyendo lista de recuros disponibles...\n");

  ssize_t read;
  size_t len = 0;

  for(int i =0; i < totalRecursos; i++) {
    machines[i] = malloc(sizeof(char)*bufsize);
    read = getline(&machines[i], &len, fMachines);
    machines[i][strlen(machines[i]) - 1] = '\0';
    //getline(&machines[i], &bufsize, fMachines);
    //printf("Recurso disponible: %s \n", machines[i] );
    lista_recursos[i] = 0;
  }
  fclose(fMachines);

  char buffArg[200];

  char *args[] = {"sh", "-c",
   // " ssh c-00-00 \"sumaAleatorios 10000 ../output/salida10.txt\""
    //"./sumaAleatorios 1000 ./output/salida0000.txt"
    buffArg, NULL};
 
//  pid_t *pids = malloc(sizeof(pid_t)*N);
  int status;

  pid_t pidActual, recurso_disp;
 
  int numProcesos = 0;
  int enEjecucion = 0;

  while ( numProcesos < totalTareas) {
    //(read = getline(&buffer, &len, fTasks)) > 5) {
    // leer tarea:
//    fscanf(fTasks,"%[^\n]", buffer);
    getline(&buffer, &bufsize, fTasks);
    buffer[strlen(buffer) - 1] = '\0';

    // Buscar un recurso disponible
    recurso_disp = -1;

    for(int i=0; i < totalRecursos; i++ ) {
      if (lista_recursos[i] == 0) {
        recurso_disp = i;
        break;
      }
    }


    if (recurso_disp < 0) {
      // Espera a que se libere un recurso:
      pid_t idTermino = wait(&status);
      //printf("Termino de ejecutar el proceso: %d \n", pidActual);
      enEjecucion--;

      // Una vez que un proceso termino, buscamos el recurso libre
      // Y lo liberamos:
      for(int i=0; i < totalRecursos; i++) {
        if (lista_recursos[i] == idTermino) {
         recurso_disp = i;
         lista_recursos[i] = 0;
        }
      }
    }

    usleep(10000); // Espera 0.01 segundos
    pidActual = fork();
  
    if ( pidActual == 0 ) { /* hijo */
      //printf("Soy el hijo %d (%d, hijo de %d)\n", numProcesos+1, getpid(), getppid());      

      //sprintf(args[2], "ssh %s \"%s\"", machines[recurso_disp], buffer);
      sprintf(args[2], " %s \"%s\"", machines[recurso_disp], buffer);

      //printf("Se ejecutara la tarea: 'sh -c %s'\n", args[2] );

      // Ejecuta el programa usando recurso_dis
      execv("/bin/sh", args);
    
      //printf("Esto ya no deberia imprimirse\n");
      //printf("Se ha producido un error al ejecutar execv.\n");
      //exit(0);
    } else { /*  padre */
      // registra el proceso creado:
      //pids[numProcesos++] = pidActual;
      numProcesos++;
      enEjecucion++;
      // Registra recurso_dis ocupado por el proceso creado:
      lista_recursos[recurso_disp] = pidActual;
    }    
  }
  for(int i=0; i < enEjecucion; i++) {
    //pidActual = wait( &(status[i]));
    pidActual = wait(&status);
    //printf("Termino de ejecutar el proceso: %d \n", pidActual);
  }
  fclose(fTasks);
  //free(pids);

  for(int i =0; i < totalRecursos; i++) {
    free(machines[i]);
  }

//  printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
//  printf("se ejecutaron todos los procsos hijos.\n");

  
  //printf("Se ha producido un error al ejecutar execv.\n");
 
  return 0;
}