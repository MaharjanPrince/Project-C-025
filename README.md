# Maze Solver in C
This program implements a Maze Solver using two common algorithms: 
Breadth-First Search (BFS) and Depth-First Search (DFS). 
It reads a maze input from the user and solves it by finding the shortest path from the start ('S') to the end ('E'). 
The maze is represented as a 2D grid, where:
'0' represents an open path.
'1' represents a wall.
'S' marks the start point.
'E' marks the endpoint.
The program provides both BFS and DFS approaches to solve the maze and visualizes the result by marking the solution path with '*' characters.

Features:
BFS (Breadth-First Search): Finds the shortest path from 'S' to 'E' and prints the path length.
DFS (Depth-First Search): Explores the maze and marks the solution path from 'S' to 'E'.
Visualization: The maze is displayed with walls, open paths, start, end, and solution paths.

#How to Use:
Input:
Enter the number of rows and columns for the maze.
Enter the maze as a grid of 0s (paths), 1s (walls), S (start), and E (end).
The program will output the shortest path using BFS and the solution path using DFS.
