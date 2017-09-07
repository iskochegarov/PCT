#define _POSIX_C_SOURCE 1
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <omp.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

double getrand(unsigned int *seed)
{
    return (double)rand_r(seed) / RAND_MAX;
}

double func(double x, double y)
{ 
    return 3 * pow(y, 2) * pow(sin(x), 2); 
}

const double PI = 3.14159265358979323846;
const int n = 10000000;

int main(int argc, char **argv)
{
    int in = 0;
    double s = 0;
    double t;
    t = wtime();
    #pragma omp parallel
    {
        double s_loc = 0;
        int in_loc = 0;
        unsigned int seed = omp_get_thread_num();
        
        #pragma omp for nowait
        for (int i = 0; i < n; i++) {
            double x = getrand(&seed) * PI; /* x in [0, pi] */
            double y = getrand(&seed);      /* y in [0, sin(x)] */
            if (y <= sin(x)) {
                in_loc++;
                s_loc += func(x, y);
            }
        }   
        #pragma omp atomic
            s += s_loc;
        #pragma omp atomic
            in += in_loc;
    }

    double v = PI * in / n;
    double res = v * s / in;
    
    t = wtime() - t;
    
    double serial = 1.526030;
    double speedup = serial/t;
    printf("Elapsed time: %.6f sec.\n", t); 
    printf("Speedup = %f\n", speedup);
    printf("\n\nResult: %.12f, n %d\n", res, n);
    return 0;
}
