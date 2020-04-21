#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *factorial (void *arg);

int main (int argc, char *argv[]) {
  srand(time(0));
  if (argc == 3) {

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, factorial, argv[1]);
    pthread_create(&thread2, NULL, factorial, argv[2]);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

  }
  
  return 0;
}

void *factorial (void *arg) {
  long long int resultado = 1;
  int n = atoi((char *) arg);
  int num;

  for (num= 2; num<= n; num++) {
    resultado= resultado* num;
    printf ("Factorial de %d, resultado parcial %lld\n", n, resultado);
    sleep (random() %3);
  }

  printf ("Factorial de %d es : %lld\n", n, resultado);
  pthread_exit(NULL);
}
