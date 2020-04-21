#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *factorial (void *arg);

int main (int argc, char *argv[]) {
  srand(time(0));
  if (argc >= 2) {

    pthread_t threads[argc-1];

    for(int i = 0; i < argc-1; i++){
      pthread_create(&threads[i], NULL, factorial,argv[i+1]);
    }

    for (int i= 0; i < argc-1; i++) {
      pthread_join (threads[i], NULL);
      printf("Se ha finalizado el hilo %d \n", i+1);
    }

  }
  
  return 0;
}

void *factorial (void *arg) {
  long long int resultado = 1;
  int n = atoi((char *) arg);
  int num;

  for (num= 2; num<= n; num++) {
    resultado= resultado* num;
    printf("Factorial de %d, resultado parcial %lld\n", n, resultado);
    sleep (random() %3);
  }

  printf (" EL Factorial de %d es %lld\n", n, resultado);
  pthread_exit(NULL);
}
