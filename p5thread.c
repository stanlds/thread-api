#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>

#define MAXLON 1000

void *suma(void *h1);
void vector(char *nombre, int num[], int *tamano);

typedef struct
{
    int *num;
    int inicio;
    int fin;
    int *value;
}argumentos;

int main(int argc, char *argv[])
{
    clock_t start_t = clock();
    clock_t end_t;
    double total_t = 0;

    int num[100];
    int value1 = 0;
    pthread_t t1;
    int value2 = 0;
    pthread_t t2;
    int tamano = 0;
    if (argc != 2)
    {
        printf("Indica únicamente el nombre de un fichero.\n");
        exit(0);
    }
    vector(argv[1], num, &tamano);
    argumentos h1;
    h1.num = num;
    h1.inicio = 0;
    h1.fin = (int)tamano/2;
    h1.value = &value1;

    int mitad = tamano/2+1;

    argumentos h2;
    h2.num = num;    
    h2.inicio = (int)(tamano/2);
    h2.fin = tamano;
    h2.value = &value2;


    pthread_create(&t1, NULL, suma, &h1);
    pthread_join(t1, NULL);
    pthread_create(&t2, NULL, suma, &h2);
    pthread_join(t2, NULL);

    
    printf("El valor de la suma 1 de los elementos del vector es: %d\n", value1);
    printf("El valor de la suma 2 de los elementos del vector es: %d\n", value2);
    int sumaTotal = value1 + value2;
    printf("El valor de la suma total de los elementos del vector es: %d\n", sumaTotal);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("EL tiempo de ejecucion de la CPU es: %f seg\n", total_t);
    return 0;
}

void vector(char *nombre, int num[], int *tamano)
{
    int entero = 0;
    int sum = 0;
    FILE *file;
    file = fopen(nombre, "r");
    char aux = '0';
    int auxv[100];
    int j = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            int longitud = 0;
            while (isdigit(aux))
            {
                entero = aux - '0';
                auxv[longitud] = entero;
                aux = fgetc(file);

                longitud++;
            }

            int potencia = 1;
            sum = 0;
            for (int i = 1; i <= longitud; i++)
            {
                int numero = 0;
                numero = auxv[longitud - i] * potencia;
                sum = sum + numero;
                potencia = potencia * 10;
            }
            if (sum != 0)
            {
                num[j] = sum;
                j = j + 1;
            }
            aux = fgetc(file);
        }
        *tamano = j;
    }
    else
    {
        exit(1);
    }
    fclose(file);
}

void *suma(void *h1)
{
    argumentos *args = (argumentos *)h1;
    int inicio = args->inicio;
    int fin = args->fin;
    int *value = args->value;
    int *num = args->num;

    for (int i = inicio; i < fin; i++)
    {
        *value = *value + num[i];
    }
}
