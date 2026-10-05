#include <stdio.h>
#include <string.h>

#define MAX 20
#define INF 9999

int graph[MAX][MAX];
int distance[MAX];
int visited[MAX];
int parent[MAX];
int n;

char location[MAX][50];

/* Function to enter campus graph */
void enterGraph()
{
    int i, j, d;

    printf("\nEnter number of locations: ");
    scanf("%d", &n);

    printf("\nEnter location names:\n");

    for(i = 0; i < n; i++)
    {
        printf("Location %d: ", i + 1);
        scanf(" %[^\n]", location[i]);
    }

    /* Initialize graph */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    printf("\nEnter distances between connected locations.\n");
    printf("Enter 0 if there is no direct connection.\n");

    /* Since campus roads are assumed to be undirected */
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            printf("\nDistance between %s and %s: ",
                   location[i], location[j]);

            scanf("%d", &d);

            if(d > 0)
            {
                graph[i][j] = d;
                graph[j][i] = d;
            }
        }
    }

    printf("\nCampus graph entered successfully.\n");
}

/* Function to display adjacency matrix */
void displayMatrix()
{
    int i, j;

    if(n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    printf("\n========== ADJACENCY MATRIX ==========\n\n");

    printf("%15s", "");

    for(i = 0; i < n; i++)
    {
        printf("%15s", location[i]);
    }

    printf("\n");

    for(i = 0; i < n; i++)
    {
        printf("%15s", location[i]);

        for(j = 0; j < n; j++)
        {
            if(graph[i][j] == INF)
                printf("%15s", "INF");
            else
                printf("%15d", graph[i][j]);
        }

        printf("\n");
    }
}

/* Function to select source */
int selectSource()
{
    int source;

    printf("\n========== SELECT SOURCE LOCATION ==========\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d. %s\n", i + 1, location[i]);
    }

    printf("\nEnter source location number: ");
    scanf("%d", &source);

    if(source < 1 || source > n)
    {
        printf("\nInvalid source location.\n");
        return -1;
    }

    return source - 1;
}

/* Find vertex having minimum distance */
int findMinimumDistance()
{
    int min = INF;
    int minIndex = -1;
    int i;

    for(i = 0; i < n; i++)
    {
        if(visited[i] == 0 && distance[i] < min)
        {
            min = distance[i];
            minIndex = i;
        }
    }

    return minIndex;
}

/* Dijkstra's Algorithm */
void dijkstra(int source)
{
    int i, j, u;

    /* Initialization */
    for(i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    /* Dijkstra */
    for(i = 0; i < n - 1; i++)
    {
        u = findMinimumDistance();

        if(u == -1)
            break;

        visited[u] = 1;

        for(j = 0; j < n; j++)
        {
            if(visited[j] == 0 &&
               graph[u][j] != INF &&
               distance[u] + graph[u][j] < distance[j])
            {
                distance[j] = distance[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }

    printf("\nShortest distances calculated successfully.\n");
}

/* Function to display shortest path */
void displayPath(int vertex)
{
    if(parent[vertex] == -1)
    {
        printf("%s", location[vertex]);
        return;
    }

    displayPath(parent[vertex]);
    printf(" -> %s", location[vertex]);
}

/* Display shortest paths */
void displayShortestPaths(int source)
{
    int i;

    printf("\n========== SHORTEST PATHS ==========\n\n");

    for(i = 0; i < n; i++)
    {
        if(i == source)
            continue;

        printf("%s : ", location[i]);

        if(distance[i] == INF)
        {
            printf("No path available\n");
        }
        else
        {
            displayPath(i);
            printf("   Distance = %d\n", distance[i]);
        }
    }
}

/* Display distances */
void displayDistances(int source)
{
    int i;

    printf("\n========== DISTANCE FROM SOURCE ==========\n\n");

    printf("Source Location: %s\n\n", location[source]);

    printf("%-25s %-15s\n", "Destination", "Distance");
    printf("------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        if(i == source)
        {
            printf("%-25s %-15d\n",
                   location[i], 0);
        }
        else if(distance[i] == INF)
        {
            printf("%-25s %-15s\n",
                   location[i], "INF");
        }
        else
        {
            printf("%-25s %-15d\n",
                   location[i], distance[i]);
        }
    }
}

/* Main function */
int main()
{
    int choice;
    int source = -1;

    n = 0;

    do
    {
        printf("\n\n============================================");
        printf("\n       CAMPUS SHORTEST ROUTE FINDER");
        printf("\n============================================");

        printf("\n1. Enter Campus Graph");
        printf("\n2. Display Adjacency Matrix");
        printf("\n3. Select Source Location");
        printf("\n4. Find Shortest Distance");
        printf("\n5. Display Shortest Paths");
        printf("\n6. Display Distance from Source to All Locations");
        printf("\n7. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                enterGraph();
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                if(n == 0)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else
                {
                    source = selectSource();

                    if(source != -1)
                        printf("\nSelected Source: %s\n",
                               location[source]);
                }
                break;

            case 4:
                if(n == 0)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else if(source == -1)
                {
                    printf("\nPlease select a source location first.\n");
                }
                else
                {
                    dijkstra(source);
                }
                break;

            case 5:
                if(source == -1)
                {
                    printf("\nPlease select source and find shortest distances first.\n");
                }
                else
                {
                    displayShortestPaths(source);
                }
                break;

            case 6:
                if(source == -1)
                {
                    printf("\nPlease select source and find shortest distances first.\n");
                }
                else
                {
                    displayDistances(source);
                }
                break;

            case 7:
                printf("\nProgram terminated.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while(choice != 7);

    return 0;
}