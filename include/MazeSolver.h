#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <vector>

class MazeSolver{
public:
    //constructor
    MazeSolver(int r, int c);

    //controls main workflow of the maze solver
    void run();
    void printMaze();


private:
    //dimension of the maze
    int rows, cols;

    //2D vector representing the maze grid
    std::vector<std::vector<int>> maze;

    //keeps track of visited cells during DFS to avoid revisiting
    std::vector<std::vector<bool>> visited;
    
    //start and end points
    int startX, startY;
    int endX, endY;

    //directions of x and y axis
    int dx[4];
    int dy[4];
    
    //generates maze using recursive backtacking algorithm
    void generateMaze();
    void generateRecursive(int x, int y);

    //solves maze using sequential DFS
    bool solveSequential();
    //find a path from start to end
    bool dfs(int x, int y);
    
    //solves maze using OpenMP
    bool solveParallel();
    //explores multiple paths simultaneously
    bool parallelDFS(int x, int y, bool& found);

    //checks if coordinates are inside the maze
    bool isInside(int x, int y);

    //checks if cell is valid for movement(inside, not wall, not visited)
    bool isValid(int x, int y);

    //resets visited array for another search
    void resetVisited();
};


#endif