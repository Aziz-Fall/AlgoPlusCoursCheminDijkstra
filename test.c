#include <stdio.h>
#include <stdlib.h>

#define AND        &&
#define INFINY     100
#define NO_PARENT -1
#define NB_NODE    6
#define VISITED    1

int all_nodes_are_visited(int node_visited[]);
int index_min(int node_visited[], int dist[]);
void print_path(int parent[], int begin, int end);
void update(int dist[], int parent[], int s, int k, int matrix[][NB_NODE]);
void initilization(int dist[], int parent[], int matrix[][NB_NODE], int begin);
int main(void)
{
    int matrix[][NB_NODE] = {
                        {   0,  4,   8,  100,   11, 100  },
                        { 100,   0,   3,    2, 100, 100  },
                        { 100, 100,   0,    1,   2, 100  },
                        { 100, 100,   2,    0,   5,   7  },
                        { 100, 100, 100,  100,   0,   3  }, 
                        { 100, 100, 100,  100, 100,   0  }
                    };
     int matrix1[][NB_NODE] = {
                        {   0,  10,   3,  100,   6, 100  },
                        {   0,   0, 100,  100, 100, 100  },
                        { 100,   4,   0,  100,   2, 100  },
                        { 100, 100,   1,    0,   3, 100  },
                        { 100,   4, 100,  100,   0,   1  }, 
                        {   2,   1, 100,  100, 100,   0  }
                    };               

    int parent[NB_NODE], dist[NB_NODE], node_visited[NB_NODE] = {0};
    initilization(dist, parent, matrix, 0);
    node_visited[0] = VISITED; 
    while ( !all_nodes_are_visited(node_visited) )
    {
        int node_to_trait           = index_min(node_visited, dist);
        node_visited[node_to_trait] = VISITED;
        for( int i = 0; i < NB_NODE; i++ )
            update(dist, parent, node_to_trait, i, matrix);

    }
    
    for( int i = 0; i < NB_NODE; i++ ) 
    {
        printf("parent[%d] = %d | dist[%d] = %d\n", i+1, parent[i] + 1, i+1, dist[i]);
    }
    print_path(parent, 0, 5);
    return EXIT_SUCCESS;
}

int index_min(int node_visited[], int dist[])
{
    int min = INFINY, node = -1;
    for( int i = 0; i < NB_NODE; i++)
    {
        if( !node_visited[i] && dist[i] <= min )
        {
            min  = dist[i];
            node = i;
        }
    }
    return node;
}

void initilization(int dist[], int parent[], int matrix[][NB_NODE], int begin)
{
    for( int i = 0; i < NB_NODE; i++)
    {
        parent[i] = ( matrix[begin][i] == INFINY )? NO_PARENT : begin;
        
        dist[i] = matrix[begin][i];
    }    
    dist[begin]   = 0;
    parent[begin] = NO_PARENT;
}

void update(int dist[], int parent[], int t, int k, int matrix[][NB_NODE])
{
    if( dist[k] > dist[t] + matrix[t][k] )
    {
        dist[k] = dist[t] + matrix[t][k];
        parent[k] = t;
    }
}

int all_nodes_are_visited(int node_visited[])
{
    for( int i = 0; i < NB_NODE; i++)
        if( !node_visited[i] )
            return 0;

    return 1;
}

void print_path(int parent[], int begin, int end)
{
    int e = end;
    while(e != begin)
    {
        printf("%d <-", e + 1);
        e = parent[e];
    }
    printf("%d\n", e + 1);
}