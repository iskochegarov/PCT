/*
 * counter.c:
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main(int argc, char *argv[])
{
    int n = 100000000;
    int *v = malloc(sizeof(*v) * n);

    for (int i = 0; i < n; i++)
        v[i] = rand() % 30;

    double t = wtime();
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (v[i] == 3)
            count++;
    }

    t = wtime() - t;

    printf("Counter (parallel, n = %d)\n", n);
    printf("Count = %d\n", count);
    printf("Time (sec): %.6f\n", t);

    free(v);
    return 0;
}
