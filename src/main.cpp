#include <iostream>
#include "MazeManager.h"
#include "MazeGenerator.h"
#include "SequentialDfsSolver.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        std::cerr << "Maze size must be an odd integer greater than or equal to 5." << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
        if (n < 5 || n % 2 == 0)
        {
            std::cerr << "Maze size must be an odd integer greater than or equal to 5." << std::endl;
            return 1;
        }

    try
    {
        const char *mazeFile = "try_maze.txt";
        const char *solutionFile = "try_solution.txt";
        MazeGenerator generator;
        generator.generateMaze(n, mazeFile);

        SequentialDfsSolver solver;
        solver.solveMazeWithSeqDfs(mazeFile, solutionFile);
        solver.printSolution(solutionFile);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}