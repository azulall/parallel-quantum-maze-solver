#include "SequentialDfsSolver.h"
#include "MazeManager.h"

bool SequentialDfsSolver::followPath(std::vector<std::vector<int>> &maze, std::vector<std::vector<int>> &solution, int x, int y, int end_x, int end_y)
{
    if (x < 0 || x >= maze[0].size() || y < 0 || y >= maze.size() || maze[y][x] == WALL || solution[y][x] == 8)
    {
        return false;
    }

    solution[y][x] = 8; 

    if (x == end_x && y == end_y)
    {
        printf("Reached the end point at (%d, %d)\n", x, y);
        return true;
    }
    
    if (followPath(maze, solution, x + 1, y, end_x, end_y) || 
        followPath(maze, solution, x - 1, y, end_x, end_y) ||
        followPath(maze, solution, x, y + 1, end_x, end_y) || 
        followPath(maze, solution, x, y - 1, end_x, end_y))
    {
        return true;
    }

    solution[y][x] = 0; // Backtrack
    return false;
}




void SequentialDfsSolver::solveMazeWithSeqDfs(const char *mazeFile, const char *solutionFile)
{
    MazeManager manager;

    int n;
    manager.getMazeSizeFromFile(mazeFile, n);

    int start_x, start_y, end_x, end_y;

    manager.getStartIndicesFromFile(mazeFile, start_x, start_y);
    manager.getEndIndicesFromFile(mazeFile, end_x, end_y);

    printf("Start point: (%d, %d)\n", start_x, start_y);
    printf("End point: (%d, %d)\n", end_x, end_y);

    std::vector<std::vector<int>> maze;
    manager.getMazeFromFile(mazeFile, maze, n);

    std::vector<std::vector<int>> solution = maze;

    
    if (followPath(maze, solution, start_x, start_y, end_x, end_y))
    {
        std::cout << "Path found from start to end." << std::endl;
    } else {
        std::cerr << "No path found from start to end." << std::endl;
    }

    manager.saveMazeToFile(solution, n, start_x, start_y, end_x, end_y, solutionFile);
}



void SequentialDfsSolver::printSolution(const char *filename)
{
    MazeManager manager;
    int n;
    manager.getMazeSizeFromFile(filename, n);
    manager.printMaze(filename, n);

}
