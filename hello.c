#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
    omp_set_num_threads(3); // thread sayisini ata
    // paralellestirme blogu    
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("Hello %d\n", ID);
    }
    return 0;
}

