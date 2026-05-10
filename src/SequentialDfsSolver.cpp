#include "SequentialDfsSolver.h"
#include "MazeManager.h"
#include <stack>

// Iterative DFS path finder using explicit stack
// Avoids stack overflow on large mazes (1001x1001)
bool SequentialDfsSolver::followPath(std::vector<std::vector<int>> &maze, std::vector<std::vector<int>> &solution, int x, int y, int end_x, int end_y)
{
    int rows = (int)maze.size();
    int cols = (rows > 0) ? (int)maze[0].size() : 0;

    // Direction arrays: right, left, down, up
    int ddx[] = {1, -1, 0, 0};
    int ddy[] = {0, 0, 1, -1};

    // Stack frame: x, y, direction index
    struct Frame {
        int x, y;
        int dirIdx;
    };

    std::stack<Frame> callStack;

    // Check if start is valid
    if (x < 0 || x >= cols || y < 0 || y >= rows || maze[y][x] == WALL) {
        return false;
    }

    solution[y][x] = 8; // Mark as visited
    callStack.push({x, y, 0});

    while (!callStack.empty()) {
        Frame &cur = callStack.top();

        // Check if we reached the end
        if (cur.x == end_x && cur.y == end_y) {
            printf("Reached the end point at (%d, %d)\n", cur.x, cur.y);
            return true;
        }

        if (cur.dirIdx >= 4) {
            // All directions tried, backtrack
            solution[cur.y][cur.x] = 0;
            callStack.pop();
            continue;
        }

        int nx = cur.x + ddx[cur.dirIdx];
        int ny = cur.y + ddy[cur.dirIdx];
        cur.dirIdx++;

        // Check if next cell is valid
        if (nx >= 0 && nx < cols && ny >= 0 && ny < rows
            && maze[ny][nx] != WALL && solution[ny][nx] != 8) {
            solution[ny][nx] = 8;
            callStack.push({nx, ny, 0});
        }
    }

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
