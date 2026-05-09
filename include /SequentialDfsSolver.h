#ifndef SEQUENTIAL_DFS_SOLVER_H
#define SEQUENTIAL_DFS_SOLVER_H

#include "MazeGenerator.h"

class SequentialDfsSolver
{
public:
    SequentialDfsSolver() = default;
    bool followPath(std::vector<std::vector<int>> &maze, std::vector<std::vector<int>> &solution, int x, int y, int end_x, int end_y);
    void solveMazeWithSeqDfs(const char *mazeFile, const char *solutionFile);
    void printSolution(const char *solutionFile);
};

#endif
