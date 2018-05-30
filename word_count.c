#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "map.h"

int main(int argc, char** argv)
{
    int num_threads = 2;
    omp_set_num_threads(num_threads); // sets number of threads.
    // if not set threads as many as cpu cores
    // a, b, func, steps
    if(argc !=2)
    {
        printf("Invalid argument count\n");
        return 127;
    }

    char* text = argv[1];
    long txt_len = strlen(text);
    long local_steps = (long)ceil((float)txt_len / num_threads);
    printf("%ld %ld\n", local_steps, txt_len);
    map_int_t m;
    map_init(&m);
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        long a = local_steps * ID;
        long b = local_steps * (ID+1); // burdaki mantigi duzelt TODO
        
        char *part = (char*)calloc(sizeof(char),(b-a));
        strncpy(part,&text[a], b-a);
        printf("Part: %s\n", part);
        char *token = strtok(part," \t\n");

        while(token != NULL){
            int* val = map_get(&m, token);
            if(val == NULL)
            {
                map_set(&m, token, 1);
            }
            else
            {
                int v = *(val);
                map_set(&m, token, v+1);
            }

            token = strtok(NULL," \t\n");
        }
    }
    map_iter_t iter = map_iter(&m);
    const char* key;
    while((key=map_next(&m, &iter)))
    {
        printf("%s: %d\n", key, *map_get(&m, key));
    }
    map_deinit(&m);
    return 0;
}

