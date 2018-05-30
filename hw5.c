#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
    int graph_adj[4][4] = {
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4}
    };
    // paralellestirme blogu 
     
    #pragma omp parallel for 
    for(int i=0;i<4;i++)
    {    
        for(int j=0;j<4;j++) {
            if(graph_adj[i][j] == 3) {
                printf("%d %d\n", i, j);
            }
        }
    }
    return 0;
}

