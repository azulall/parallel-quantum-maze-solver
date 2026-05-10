#include <iostream>
#include <chrono>
#include <vector>

// All project modules
#include "MazeGenerator.h"
#include "MazeManager.h"
#include "SequentialDfsSolver.h"
#include "MazeSolver.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    // Maze size can be passed as command line argument (must be odd)
    // Default is 1001 for good speedup demonstration
    int n = 1001;
    if (argc > 1) {
        n = atoi(argv[1]);
        if (n % 2 == 0) n++; // maze size must be odd for proper generation
    }
    const char* mazeFile = "maze_test.txt";
    const char* seqSolutionFile = "solution_seq.txt";

    cout << "========================================================\n";
    cout << "    QUANTUM-INSPIRED PARALLEL MAZE SOLVER    \n";
    cout << "========================================================\n\n";

    // Step 1: Generate the maze using recursive backtracking
    cout << "[1/4] Generating maze (" << n << "x" << n << ")...\n";
    MazeGenerator generator;
    generator.generateMaze(n, mazeFile);
    cout << "      Maze saved to '" << mazeFile << "'\n\n";

    // Step 2: Solve with sequential DFS (baseline measurement)
    cout << "[2/4] Running Sequential DFS (baseline)...\n";
    SequentialDfsSolver seqSolver;

    auto start_seq = high_resolution_clock::now();
    seqSolver.solveMazeWithSeqDfs(mazeFile, seqSolutionFile);
    auto end_seq = high_resolution_clock::now();

    duration<double, std::milli> seq_time = end_seq - start_seq;
    cout << "      Sequential DFS completed! Time: " << seq_time.count() << " ms\n\n";

    // Step 3: Load maze data for the parallel solver
    cout << "[3/4] Loading maze data for parallel engine...\n";
    MazeManager manager;
    int size_n, sx, sy, ex, ey;
    vector<vector<int>> mazeMatrix;

    manager.getMazeSizeFromFile(mazeFile, size_n);
    manager.getStartIndicesFromFile(mazeFile, sx, sy);
    manager.getEndIndicesFromFile(mazeFile, ex, ey);
    manager.getMazeFromFile(mazeFile, mazeMatrix, size_n);

    // Step 4: Solve with quantum-inspired parallel solver
    cout << "[4/4] Running Quantum-Inspired OpenMP Parallel Solver...\n";

    MazeSolver parSolver(size_n, size_n);
    // Load the maze data: sx = start column, sy = start row (file format)
    parSolver.loadMaze(mazeMatrix, sx, sy, ex, ey);

    auto start_par = high_resolution_clock::now();
    bool isFound = parSolver.solveParallel();
    auto end_par = high_resolution_clock::now();

    duration<double, std::milli> par_time = end_par - start_par;

    if (isFound) {
        cout << "      Parallel solver found the path! Time: " << par_time.count() << " ms\n\n";
    } else {
        cout << "      WARNING: Parallel solver could not find a path!\n\n";
    }

    // Performance report
    cout << "========================================================\n";
    cout << "                 PERFORMANCE REPORT                      \n";
    cout << "========================================================\n";
    cout << " Sequential DFS Time   : " << seq_time.count() << " ms\n";
    cout << " Parallel Solver Time  : " << par_time.count() << " ms\n";

    if (par_time.count() > 0) {
        double speedup = seq_time.count() / par_time.count();
        cout << " SPEEDUP               : " << speedup << "x FASTER\n";
    }
    cout << "========================================================\n";

    return 0;
}
