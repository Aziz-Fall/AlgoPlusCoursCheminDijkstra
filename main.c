#include <stdio.h>
#include <stdlib.h>

#define AND        &&
#define INFINY     100
#define NO_PARENT -1
#define NB_NODE    6
#define VISITED    1

int sum_tab(int tab[]);
int index_min_tab(int tab[], int node_visited[]);
int *init_tab_parent(int *distance, int matrix[][NB_NODE], int line);
void djisktra(int distance[], int matrix[][NB_NODE], int line, int tab_parent[]);

int main(void)
{
    int matrix[][NB_NODE] = {
                        {   0,  10,   3,  100,   6, 100  },
                        {   0,   0, 100,  100, 100, 100  },
                        { 100,   4,   0,  100,   2, 100  },
                        { 100, 100,   1,    0,   3, 100  },
                        { 100,   4, 100,  100,   0,   1  }, 
                        {   2,   1, 100,  100, 100,   0  }
                    };

    int *tab = NULL; 
    int  distance[NB_NODE] = {0}, visited[NB_NODE] = {1, 0, 1, 0, 0, 0};

    tab = init_tab_parent(distance, matrix, 0);
    for(int i = 0; i < NB_NODE; i++)
        printf("NODE[%d]: %2d  | distance[%d]: %d\n", i + 1, tab[i], i + 1, distance[i]);
    printf("index_min: %d\n", index_min_tab(distance, visited));
    printf("Sum: %d\n", sum_tab(distance));

    djisktra(distance, matrix, 0, tab);

    for(int i = 0; i < NB_NODE; i++)
        printf("parent[%d] = %d\n", (i + 1), tab[i] + 1);
        
    return EXIT_SUCCESS;
}


int *init_tab_parent(int *distance, int matrix[][NB_NODE], int line)
{
    static int tab_parent[NB_NODE] = {0};
    for(int i = 0; i < NB_NODE; i++)
    {
        if(matrix[line][i] == INFINY)
        {
            tab_parent[i] = NO_PARENT;
            distance[i]   = INFINY;
        } 
        else
        {
            distance[i]   = matrix[line][i];
            tab_parent[i] = line;
        }   
    }
    tab_parent[line] = NO_PARENT;
    return tab_parent;
}

int index_min_tab(int tab[], int node_visited[])
{
   int continu = 1, min = 0, index_min = 0;

   for(int i = 0; i < NB_NODE AND continu; i++)
   {
       if(!node_visited[i])
       {
           min     = tab[i];
           continu = 0;
       }
   }

    for(int i = 0; i < NB_NODE; i++)
    {
        if(!node_visited[i])
            if(min > tab[i])
            {
                min = tab[i];
                index_min = i;
            }
    }
    return index_min;
}

int sum_tab(int tab[])
{
    int sum = 0;
    for(int i = 0; i < NB_NODE; sum += tab[i++]);
    return sum;
}

void djisktra(int distance[], int matrix[][NB_NODE], int line, int tab_parent[])
{
    int node_visited[NB_NODE] = {0}, d_t = 0, continu = 1;
    node_visited[line] = VISITED;

    while(sum_tab(node_visited) != NB_NODE AND continu )
    {
        int index_min = index_min_tab(distance, node_visited);
        
        node_visited[index_min] = VISITED;
        d_t = distance[index_min];

        for(int k = 0; k < NB_NODE; k++)
        {
            if( (distance[k] > distance[index_min] + matrix[index_min][k]) && k != index_min )
            {
                distance[k]   = distance[index_min] + matrix[index_min][k];
                tab_parent[k] = index_min; 
            }
        }
        printf("index_min: %d\n", index_min);
        continu = (index_min == 0) ? 0 : 1;
    }
}
