#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
    int num_threads = 8;
    omp_set_num_threads(num_threads); // 
    // if not set threads as many as cpu cores
    // a, b, func, steps
    long total_steps = 9000;
    long local_steps = total_steps / num_threads;
    double sum_total = 0.0;
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        long a = local_steps * ID;
        long b = local_steps * (ID+1);
        int i = a;
        double sum = 0.0;
        double h = 1.0 / total_steps;
        double x = 0.0;
        for(i;i<b;i++)
        {
            x = (i+0.5)*h;
            sum += 4.0/(1+x*x);
        }
        printf("%lf\n", sum*h);
        #pragma omp atomic
            sum_total +=sum*h;
    }
    printf("%lf\n", sum_total);
    return 0;
}

