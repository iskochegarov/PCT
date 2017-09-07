#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h> 
#include <math.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

double getrand()
{ return (double)rand() / RAND_MAX; }

double func(double x, double y)
{ return 3 * pow(y, 2) * pow(sin(x), 2); }

const double PI = 3.14159265358979323846;
const int n = 10000000;

int main(int argc, char **argv)
{
    int in = 0;
    double s = 0;
    double t;
    t = wtime();
    for (int i = 0; i < n; i++) {
        double x = getrand() * PI;
        double y = getrand();
        if (y <= sin(x)) {
            in++;
            s += func(x, y);
        }
    }

    double v = PI * in / n;
    double res = v * s / in;
    t = wtime() - t;
    printf("Elapsed time: %.6f sec.\n", t); 
    printf("\n\nResult: %.12f, n %d\n", res, n);
    return 0;
}
