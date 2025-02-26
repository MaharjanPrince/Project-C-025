#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100 // Maximum maze size

// Node structure for BFS
typedef struct
{
    int x, y, dist;
} Node;

// Queue structure for BFS
typedef struct
{
    Node queue[MAX * MAX];
    int front, rear;
} Queue;

// Global variables for maze dimensions and data
int rows, cols;
char maze[MAX][MAX], temp[MAX][MAX];
bool visited[MAX][MAX];
int startX, startY, endX, endY;
bool found = false;

// Directions: Up, Right, Down, Left (DFS and BFS)
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

// Global direction arrays
int dx1[4], dy1[4];

// Function to enqueue for BFS
void enqueue(Queue *q, int x, int y, int dist)
{
    q->queue[q->rear++] = (Node){x, y, dist};
}

// Function to dequeue for BFS
Node dequeue(Queue *q)
{
    return q->queue[q->front++];
}

// Check if queue is empty (BFS)
int isEmpty(Queue *q)
{
    return q->front == q->rear;
}

// Function to read the maze from user input
void readMaze()
{
    printf("Enter the number of rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2)
    {
        printf("Invalid input for rows and columns.\n");
        exit(1); // Exit the program if input is invalid
    }

    // Read each row of the maze
    printf("Enter the maze (%d x %d) using 0 for path, 1 for wall, S for start, E for end:\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        if (scanf("%s", maze[i]) != 1)
        {
            printf("Error reading maze row.\n");
            exit(1); // Exit the program if input is invalid
        }
    }
    // To copy to temp
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            temp[i][j] = maze[i][j];
        }
    }

    // Find the start and end positions in the maze
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 'S')
            {
                startX = i;
                startY = j;
            }
            if (maze[i][j] == 'E')
            {
                endX = i;
                endY = j;
            }
        }
    }
}

// Function to print the maze (visualization)
void printMaze()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == '0')
                printf("   "); // Walkable path
            else if (maze[i][j] == '1')
                printf(" | "); // Wall
            else if (maze[i][j] == 'S')
                printf(" S "); // Start point
            else if (maze[i][j] == 'E')
                printf(" E "); // End point
            else if (maze[i][j] == '*')
                printf(" * "); // Solution path
        }
        printf("\n");
    }
}

// BFS Algorithm
int BFS(char maze[MAX][MAX], int startX, int startY, int endX, int endY)
{
    int visited[MAX][MAX] = {0};
    Queue q = {.front = 0, .rear = 0};
    int prev[MAX][MAX][2] = {-1}; // To store the previous node for each visited node

    enqueue(&q, startX, startY, 0);
    visited[startX][startY] = 1;

    while (!isEmpty(&q))
    {
        Node current = dequeue(&q);

        // Check if we've reached the end
        if (current.x == endX && current.y == endY)
        {
            // Backtrack to mark the solution path
            int x = endX, y = endY;
            while (x != startX || y != startY)
            {
                maze[x][y] = '*';
                int tempX = prev[x][y][0], tempY = prev[x][y][1];
                x = tempX;
                y = tempY;
            }
            maze[startX][startY] = 'S'; // Restore start position
            maze[endX][endY] = 'E';     // Restore end position
            return current.dist;        // Shortest path length
        }

        // Explore all 4 directions
        for (int i = 0; i < 4; i++)
        {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            // Check maze boundaries and valid paths
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                (maze[newX][newY] == '0' || maze[newX][newY] == 'E') && !visited[newX][newY])
            {
                enqueue(&q, newX, newY, current.dist + 1);
                visited[newX][newY] = 1;
                prev[newX][newY][0] = current.x; // Store previous node
                prev[newX][newY][1] = current.y; // Store previous node
            }
        }
    }
    return -1; // No path found
}

void setDirectionOrder()
{
    char order[5]; // 4 characters + null terminator
    printf("Enter order of directions (e.g., LRUD for Left, Right, Up, Down): ");
    scanf("%4s", order); // Read up to 4 characters

    if (strlen(order) != 4)
    {
        printf("Please enter exactly 4 characters (L, R, U, D).\n");
        exit(1);
    }

    for (int i = 0; i < 4; i++)
    {
        char d = order[i];
        if (d == 'L' || d == 'l')
        {
            dx1[i] = 0;  // Row change: none
            dy1[i] = -1; // Column change: left
        }
        else if (d == 'R' || d == 'r')
        {
            dx1[i] = 0;
            dy1[i] = 1;
        }
        else if (d == 'U' || d == 'u')
        {
            dx1[i] = -1; // Row change: up
            dy1[i] = 0;
        }
        else if (d == 'D' || d == 'd')
        {
            dx1[i] = 1; // Row change: down
            dy1[i] = 0;
        }
        else
        {
            printf("Invalid direction character: %c\n", d);
            exit(1);
        }
    }
}

// DFS Function (Recursive)
bool dfs(int x, int y)
{
    if (x < 0 || y < 0 || x >= rows || y >= cols || maze[x][y] == '1' || visited[x][y])
        return false;

    visited[x][y] = true;

    if (x == endX && y == endY)
        return true;

    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx1[i];
        int newY = y + dy1[i];

        if (dfs(newX, newY))
        {
            maze[x][y] = '*'; // Mark path
            return true;
        }
    }

    return false;
}

// Function to solve the maze using DFS
void solveWithDFS()
{
    // To get original maze with no changes
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            maze[i][j] = temp[i][j];
        }
    }
    setDirectionOrder();
    // Initialize visited array
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            visited[i][j] = false;

    dfs(startX, startY);
    
    printf("\nSolved Maze using DFS:\n");
    maze[startX][startY] = 'S'; // Restore start position
    maze[endX][endY] = 'E';     // Restore end position
    printMaze();
}

int main()
{
    readMaze(); // Input maze

    printf("\nSolving maze using BFS...\n");
    int result = BFS(maze, startX, startY, endX, endY);
    if (result != -1)
    {
        printf("Shortest path length using BFS is: %d\n", result);
        printMaze(); // Print the maze with the BFS solution path
    }
    else
    {
        printf("\nNot solvable");
        exit(1);
    }

    printf("\nSolving maze using DFS...\n");
    solveWithDFS(); // Solve and visualize using DFS

    return 0;
}
