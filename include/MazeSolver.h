#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <vector>

// Represents a candidate cell used in parallel search
struct SearchNode {
    int x;      // column index
    int y;      // row index
    int depth;  // current search depth for task creation control
};

class MazeSolver {
public:
    // Constructor: sets up maze grid dimensions
    MazeSolver(int r, int c);

    // Loads external maze data into the solver
    // sx, sy: start column and row; ex, ey: end column and row
    void loadMaze(const std::vector<std::vector<int>>& mazeData,
                  int sx, int sy, int ex, int ey);

    // Main workflow controller
    void run();
    // Prints the maze grid to console
    void printMaze();

    // Parallel solver entry point using OpenMP (Zulal)
    bool solveParallel();

private:
    // Maze dimensions
    int rows, cols;

    // 2D maze grid: 1 = wall, 0 = path, 2 = solution path
    std::vector<std::vector<int>> maze;

    // Flat visited array for atomic operations in parallel search
    // Index formula: y * cols + x (row * cols + col)
    std::vector<int> visited;

    // Start and end coordinates (x = column, y = row)
    int startX, startY;
    int endX, endY;

    // Direction arrays for neighbor exploration
    int dx[4];
    int dy[4];

    // Maximum depth for creating new OpenMP tasks
    static const int TASK_DEPTH_LIMIT = 6;

    // Parallel Candidate Preparation (Medine)
    std::vector<SearchNode> getParallelCandidates(int x, int y, int depth);
    std::vector<SearchNode> createInitialFrontier(int maxDepth);
    bool shouldCreateTask(int depth);

    // Parallel DFS engine (Zulal)
    bool parallelDFS(int x, int y, bool& found, int depth);
    bool tryVisitCell(int x, int y);

    // Quantum-Inspired Ordering (Kubra)
    double calculateWeight(const SearchNode& node);
    std::vector<SearchNode> orderCandidatesByWeight(std::vector<SearchNode> candidates);

    // Helper functions
    bool isInside(int x, int y);
    bool isValid(int x, int y);
    void resetVisited();
    void clearSolution();
};

#endif
