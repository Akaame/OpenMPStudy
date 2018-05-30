#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

void print_matrix(int** data, int k, int m)
{
    int i = 0;
    for(i;i<k;i++)
    {
        int j = 0;
        for(j;j<m;j++)
        {
            printf("%d ", data[i][j]);   
        }    
        printf("\n");
    }
}
int is_good_pixel(int pixel_rgba)
{
    if(pixel_rgba>2)
    {
        return 1;    
    }
    return 0;
}

int main(int argc, char** argv)
{
    int num_threads = 4;
    omp_set_num_threads(num_threads); // sets number of threads.
    // if not set threads as many as cpu cores
    // a, b, func, steps
    int k = 6400;
    int m = 4800;
    
    int** mask = malloc(sizeof(int*) * k);
    int** data = malloc(sizeof(int*) * k);
    int counter = 0;
    for(counter;counter<k;counter++)
    {
        mask[counter] = malloc(sizeof(int)*m);
        data[counter] = malloc(sizeof(int)*m);
    }
    // k m n
    int i = 0;
    int j = 0;
    for(i;i<k;i++)
    {
        j=0;
        for(j;j<m;j++)
        {
            data[i][j] = rand()%4;
        }
    }
    int total_size = k * m;
    int local_size = (int)ceil(total_size/num_threads);
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        int a = ID*local_size;
        int b = (ID+1)*local_size;
        if(b>=total_size)
        {
            b = total_size;
        }
        for(a; a<b;a++)
        {
            int i = a/k;
            int j = a%k;
            int val = is_good_pixel(data[i][j]);
            mask[i][j] = val;
        }
    }
    // print_matrix(data, k, m);
    // printf("\n");
    // print_matrix(mask, k, m);
    return 0;
}

