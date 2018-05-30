#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
    int num_threads = 8;
    omp_set_num_threads(num_threads); // 
    
    double global_a = 1.0;
    double global_b = 10.0;
    long global_steps = 10000000;
    long local_steps = global_steps / num_threads;
    double h = (global_b-global_a) / global_steps;
    double sum_total = 0.0;
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        double a = (local_steps * ID)*h + global_a;
        double b = a+(local_steps*h);
        
        if(ID == num_threads)
        {
            b = global_b;
        }
        double sum = 0.0;
        for(;a<=b;a+=h)
        {
            sum += a*a + a*2;
        }
        printf("%lf\n", sum*h);
        #pragma omp atomic
            sum_total +=sum*h;
    }
    printf("%lf\n", sum_total);
    return 0;
}

