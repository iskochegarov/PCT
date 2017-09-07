#include <math.h> 
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
struct thread_data {
double sum;
//uint8_t padding[64 - sizeof(double)];
};

double func(double x)
{
    return exp(-x * x);
}

int main(int argc, char **argv)
{
    const double a = -4.0;
    const double b = 4.0;
    const int n = 10000000;
    double s = 0.0;
    double h = (b - a) / n;
    double t;
    printf("Numerical integration: [%f, %f], n = %d\n", a, b, n);
    struct thread_data sumloc[omp_get_max_threads()];
    t = omp_get_wtime();
    #pragma omp parallel
    {
        int nthreads = omp_get_num_threads();
        int tid = omp_get_thread_num();
        int points_per_thread = n / nthreads;
        int lo = tid * points_per_thread;
        int hi = (tid == nthreads - 1) ? n - 1 : lo + points_per_thread;
        sumloc[tid].sum = 0.0;
        
        for (int i = lo; i <= hi; i++)
            sumloc[tid].sum += func(a + h * (i + 0.5));
        #pragma omp atomic
        s += sumloc[tid].sum;
        
    }
    s *= h;
    t = omp_get_wtime() - t;
    printf("Elapsed time (sec.): %.12f\n", t);
    double serial_time = 0.59892;
    double speedup = serial_time/t;
    printf("Speedup: %.4f\n", speedup);
    //printf("Result Pi: %.12f\n", s * s);
    
    

    return 0;
}
