#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include <stdlib.h>

//int i, j;

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void partition(int *v, int *i, int *j, int low, int high) // return i, j
{
    //printf("Зашёл парт\n");
    *i = low;
    *j = high;
    int pivot = v[(low + high) / 2];
    do
    {
        while (v[*i] < pivot) (*i)++;
        while (v[*j] > pivot) (*j)--;
        if (*i <= *j)
        {
            int tmp = v[*i];
            v[*i] = v[*j];
            v[*j] = tmp;

            (*i)++;
            (*j)--;
        }
    }
    while (*i <= *j);
}

void quicksort(int *v, int low, int high)
{
    int i, j;

    partition(v, &i, &j, low, high);

    if (low < j)
        quicksort(v, low, j);
    if(i < high)
        quicksort(v, i, high);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Size of massive not define\n");
        exit (EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    //int threshold = atoi(argv[2]);

    char *filename = (argc > 2) ? argv[2] : NULL;

    int *v = (int*)malloc(n*sizeof(int));

    if (v == NULL)
    {
        fprintf(stderr, "Not enough memory\n");
        exit (EXIT_FAILURE);
    }

    for (int k = 0; k < n; k++)
        v[k] = getrand(0,100000);

    double t = wtime();

    quicksort(v, 0, n - 1);

    t = wtime()-t;

    //float serial_t = ;
    //float speedup = serial_t / t;
    //printf("N = %d, Speedup = %f", n, speedup);
    printf("N = %d, Time = %f", n, t);


    if (filename)
    {
        FILE *fout = fopen(filename, "w");
        if (!fout)
        {
            fprintf(stderr, "Can't save file\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < n; i++)
        {
            fprintf(fout, "%d \n", v[i]);
        }
        fclose(fout);
    }

    free(v);
    return EXIT_SUCCESS;
}

