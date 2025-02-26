//Function to read the maze from user input
void readmaze()
{
   
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter the maze (%d x %d) using 0 for path, 1 for wall, S for start, E for end:\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        scanf("%s", maze[i]);
        }
}