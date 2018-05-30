#include <stdio.h>
#include <omp.h>
#include <string.h>

int main(int argc, char** argv)
{
    if(argc !=3)
    {
        printf("Invalid argument count\n");
        return 127;
    }

    char* pattern = argv[1];
    char* text = argv[2];
    int pat_len = strlen(pattern);
    int txt_len = strlen(text);
    
    // do naive comparison
    int i = 0;
    double start = omp_get_wtime();
    for(i;i<txt_len-pat_len+1;i++)
    {
        if(strncmp(pattern, &text[i], pat_len)==0)
        {
            printf("%d\n", i);
        }
    }
    double end = omp_get_wtime();
    printf("%lf seconds\n", end-start);
    return 0;
}

