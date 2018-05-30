#include <stdio.h>

int main(int argc, char** argv)
{
    
    double global_a = 1.0;
    double global_b = 10.0;
    long global_steps = 10000000;
    double h = (global_b-global_a) / global_steps;
    double sum_total = 0.0;
    double i = global_a;
    for(i;i<=global_b;i+=h)
    {
        sum_total += i*i + i*2;
    }
    sum_total *= h;
    printf("%lf\n", sum_total);
    return 0;
}

