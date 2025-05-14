//Distance Vector Routing (DVR)

#include <stdio.h>
#include <limits.h>

#define MAX 10
int nextHop[MAX][MAX];

void printRoutingTable(int dist[MAX][MAX], int node, int nodes) 
{
	int i;
    printf("\nRouting Table for Node %d:\n", node + 1);
    printf("Destination\tCost\n");
    for (i= 0; i < nodes; i++) 
	{
        if (dist[node][i] == INT_MAX)
            printf("%d\t\tINF\n", i + 1);
        else
            printf("%d\t\t%d\n", i + 1, dist[node][i]);
    }
}

void updateTables(int dist[MAX][MAX],int nodes) 
{
	int i,j,k;
	
	for (i = 0; i < nodes; i++)
        for (j = 0; j < nodes; j++)
            if (dist[i][j] != INT_MAX)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
                
                
    for (i = 0; i < nodes; i++) 
        for (j = 0; j < nodes; j++) 
            for (k = 0; k < nodes; k++) 
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextHop[i][j] = nextHop[i][k]; 
            	}
}

void printPath(int src, int dest) 
{
    if (nextHop[src][dest] == -1) 
	{
        printf("No path exists\n");
        return;
    }
    printf("Path: %d", src + 1);
    while (src != dest) 
	{
        src = nextHop[src][dest];
        printf(" -> %d", src + 1);
    }
    printf("\n");
}

int main() 
{
    int nodes, dist[MAX][MAX];
    int i,j,d;
    int source,destination;
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter the distance matrix:\n");
    for (i = 0; i < nodes; i++) 
	{
        for (j = 0; j < nodes; j++) 
		{
            scanf("%d", &d);
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = (d == -1) ? INT_MAX : d;
        }
    }

    updateTables(dist, nodes);

    
    for (i = 0; i < nodes; i++) 
        printRoutingTable(dist, i, nodes);

    printf("\nEnter source node (1 to %d): ", nodes);
    scanf("%d", &source);
    printf("Enter destination node (1 to %d): ", nodes);
    scanf("%d", &destination);

	// convert to 0-based index
    source--;      
    destination--; 

    printf("\nShortest path from node %d to node %d is: ", source + 1, destination + 1);
    if (dist[source][destination] == INT_MAX)
        printf("INF\n");
    else
    {
        printf("%d\n", dist[source][destination]);
        printPath(source, destination);
    }
        
    return 0;
}
/*
0 1 5
1 0 2
5 2 0
*/

/*
0 4 -1 -1 2 -1
4 0 6 -1 -1 -1
-1 6 0 3 -1 3
-1 -1 3 0 -1 -1
2 -1 -1 -1 0 7
-1 -1 3 -1 7 0
*/
