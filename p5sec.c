#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>

#define MAXLON 1000

void suma(int *num, int inicio, int fin, int *value);
void vector(char *nombre, int num[], int *tamano);
int main(int argc, char *argv[])
{
    clock_t start_t = clock();
    clock_t end_t;
    double total_t = 0;

    int num[100];
    int value = 0;
    int tamano = 0;
    if (argc != 2)
    {
        printf("Indica únicamente el nombre de un fichero.\n");
        exit(0);
    }
    vector(argv[1], num, &tamano);
    suma(num, 0, tamano, &value);
    printf("El valor de la suma de los elementos del vector es: %d\n", value);
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

void suma(int *num, int inicio, int fin, int *value)
{
    for (int i = inicio; i < fin; i++)
    {
        *value = *value + num[i];
    }
}
