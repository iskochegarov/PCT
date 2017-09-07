#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdio.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

double func(double x)
{
   return exp(-x * x);
}

int main(int argc, char **argv)
{
    const double a = -4.0;
    const double b = 4.0; 
    const int n = 10000000;
    double h = (b - a) / n;
    double s = 0.0;
    
    double t = wtime();
    for (int i = 0; i < n; i++)
        s += func(a + h * (i + 0.5));
    s *= h;
    t = wtime() - t;
    
    printf("Result Pi: %.12f\n", s * s);
    printf("Elapsed time: %.12f sec.\n", t);
    return 0;
}
