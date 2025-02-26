#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100 // Maximum maze size

// Directions: Up, Right, Down, Left (DFS and BFS)
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

// Node structure for BFS
typedef struct {
    int x, y, dist;
} Node;

// Queue structure for BFS
typedef struct {
    Node queue[MAX * MAX];
    int front, rear;
} Queue;

// Global variables for maze dimensions and data
int rows, cols;
char maze[MAX][MAX];
bool visited[MAX][MAX];
int startX, startY, endX, endY;
bool found = false;

// Function to enqueue for BFS
void enqueue(Queue *q, int x, int y, int dist) {
    q->queue[q->rear++] = (Node){x, y, dist};
}

// Function to dequeue for BFS
Node dequeue(Queue *q) {
    return q->queue[q->front++];
}

// Check if queue is empty (BFS)
int isEmpty(Queue *q) {
    return q->front == q->rear;
}

// Function to print the maze (visualization)
void printMaze() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == '0')
                printf("  ");   // Walkable path
            else if (maze[i][j] == '1')
                printf("|| ");   // Wall
            else if (maze[i][j] == 'S')
                printf("S ");   // Start point
            else if (maze[i][j] == 'E')
                printf("E ");   // End point
            else if (maze[i][j] == '*')
                printf("* ");   // Solution path
        }
        printf("\n");
    }
}

// BFS Algorithm
int BFS(char maze[MAX][MAX], int startX, int startY, int endX, int endY) {
    int visited[MAX][MAX] = {0};
    Queue q = {.front = 0, .rear = 0};

    enqueue(&q, startX, startY, 0);
    visited[startX][startY] = 1;

    while (!isEmpty(&q)) {
        Node current = dequeue(&q);

        // Check if we've reached the end
        if (current.x == endX && current.y == endY) {
            return current.dist;  // Shortest path length
        }

        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            // Check maze boundaries and valid paths
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                (maze[newX][newY] == '0' || maze[newX][newY] == 'E') && !visited[newX][newY]) {
                enqueue(&q, newX, newY, current.dist + 1);
                visited[newX][newY] = 1;
            }
        }
    }
    return -1;  // No path found
}

// DFS Function (Recursive)
bool dfs(int x, int y) {
    if (x < 0 || y < 0 || x >= rows || y >= cols || maze[x][y] == '1' || visited[x][y])
        return false;

    visited[x][y] = true;

    if (x == endX && y == endY)
        return true;

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (dfs(newX, newY)) {
            maze[x][y] = '*'; // Mark path
            return true;
        }
    }

    return false;
}

// Function to solve the maze using DFS
void solveWithDFS() {
    memset(visited, 0, sizeof(visited));
    found = dfs(startX, startY);

    if (found) {
        printf("\nSolved Maze using DFS:\n");
        maze[startX][startY] = 'S'; // Restore start position
        maze[endX][endY] = 'E';     // Restore end position
        printMaze();  // Print the maze with the solution path
    } else {
        printf("\nNo solution exists.\n");
    }
}

// Function to read the maze from user input
void readMaze() {
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter the maze (%d x %d) using 0 for path, 1 for wall, S for start, E for end:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        scanf("%s", maze[i]);
    }

    // Locate Start (S) and End (E) positions
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') {
                startX = i;
                startY = j;
            } else if (maze[i][j] == 'E') {
                endX = i;
                endY = j;
            }
        }
    }
}

int main() {
    readMaze();  // Input maze

    printf("\nSolving maze using BFS...\n");
    int result = BFS(maze, startX, startY, endX, endY);
    if (result != -1) {
        printf("Shortest path length using BFS is: %d\n", result);
        printMaze();  // Print the maze with the BFS solution path
    } else {
        printf("No path found using BFS.\n");
    }

    printf("\nSolving maze using DFS...\n");
    solveWithDFS();  // Solve and visualize using DFS

    return 0;
}
