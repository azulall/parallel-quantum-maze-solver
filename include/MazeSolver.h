#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <vector>

//represents a candidate cell used in parallel search
struct SearchNode{
    int x;
    int y;
    int depth; //for control task creation in OpenMP
};

class MazeSolver{
public:
    //constructor
    MazeSolver(int r, int c);

    //controls main workflow of the maze solver
    void run();
    //prints the maze to the console
    void printMaze();


private:
    //dimension of the maze
    int rows, cols;

    //2D maze representation
    // 1 = wall, 0 = path, 2 = solution path
    std::vector<std::vector<int>> maze;

    //keeps track of visited cells during DFS to avoid revisiting
    std::vector<std::vector<bool>> visited;
    
    //start and end points
    int startX, startY;
    int endX, endY;

    //direction arrays: right, left, down, up   Medine: 0: up, 1: down, 2: left, 3: right in generator.
    //parallel candidates functions is going to be r, l, d, u.
    int dx[4];
    int dy[4];
    
    //Maze Generation: Medine Merve
    //generates maze using recursive backtacking algorithm
    // Medine: Difference? Instead of these, use generateMaze(filename, n)
    void generateMaze();
    void generateRecursive(int x, int y);

    //Sequential Solving: Medine Merve
    //solves maze using sequential DFS
    // Medine: One function,solveWithSequentialDfs.
    bool solveSequential();
    bool dfs(int x, int y);
    
    //maybe we will implement BFS -Optional-
    //bool solveBFS();

    //Parallel Candidate Preparation: Medine
    //Finds valid neighboring cells that can be explored from the current cell
    //Returns them as SearchNode objects with updated depth information
    std::vector<SearchNode> getParallelCandidates(int x, int y, int depth);
    
    //Creates an initial set of search nodes near the start position
    //This can help distribute early search work among parallel tasks
    std::vector<SearchNode> createInitialFrontier(int maxDepth);
    
    //Decides whether a new OpenMP task should be created at the given depth
    //This prevents excessive task creation in deep recursion
    bool shouldCreateTask(int depth);

    //Parallel Solver: Zülal
    //solves maze using OpenMP
    bool solveParallel();
    
    //explores multiple paths simultaneously
    bool parallelDFS(int x, int y, bool& found, int depth);
    
    //Safely checks and marks a cell as visited in the parallel search
    //Prevents multiple threads from visiting the same cell at the same time
    bool tryVisitCell(int x, int y);
    
    
    //Quantum Inspired Logic: Kübra
    
    //Calculates a quantum-inspired weight for a candidate node
    //Nodes closer to the exit receive higher priority
    double calculateWeight(const SearchNode& node);
    
    //Sorts candidate nodes according to their calculated weights
    //More promising paths are placed earlier in the list
    std::vector<SearchNode> orderCandidatesByWeight(std::vector<SearchNode> candidates);

    //Helper Functions
    //checks if coordinates are inside the maze
    bool isInside(int x, int y);
    //checks if cell is valid for movement(inside, not wall, not visited)
    bool isValid(int x, int y);
    //resets visited array for another search
    void resetVisited();
    
    //clears the previously marked solution path before running another solver
    void clearSolution();

};


#endif
