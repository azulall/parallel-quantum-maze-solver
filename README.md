# Parallel Quantum-Inspired Maze Solver

A maze solver that compares **Sequential DFS** vs **OpenMP Parallel DFS** with quantum-inspired path ordering.

## Project Overview

This project generates a random maze and solves it using two approaches:

1. **Sequential DFS** — Classic single-threaded depth-first search (baseline)
2. **Parallel Quantum-Inspired Solver** — OpenMP task-based parallel DFS with Grover-inspired amplitude ordering

The quantum-inspired ordering prioritizes paths closer to the exit, combined with multi-threaded parallel exploration for significant speedup.

## Project Structure

| File | Description |
|------|-------------|
| `src/main.cpp` | Main program — runs both solvers and reports performance |
| `src/MazeGenerator.cpp` | Maze generation using iterative recursive backtracking |
| `src/MazeManager.cpp` | File I/O for maze data |
| `src/SequentialDfsSolver.cpp` | Sequential DFS solver (baseline) |
| `src/ParallelCandidates.cpp` | Parallel candidate cell preparation |
| `src/QuantumHeuristic.cpp` | Quantum-inspired amplitude weighting |
| `src/ParallelSolver.cpp` | OpenMP parallel DFS engine |
| `src/MazeSolverCore.cpp` | MazeSolver class core utilities |
| `sunum.html` | Project presentation (Turkish) |

## Requirements

- **GCC with OpenMP support** (on macOS: `brew install gcc`)
- C++17

## Build & Run

```bash
# Clone the repository
git clone https://github.com/azulall/parallel-quantum-maze-solver.git
cd parallel-quantum-maze-solver

# Build
make clean && make

# Run with default size (1001x1001)
OMP_STACKSIZE=64M ./maze

# Run with custom maze size (must be odd number)
OMP_STACKSIZE=64M ./maze 501
OMP_STACKSIZE=64M ./maze 2001
```

> **Note:** `OMP_STACKSIZE=64M` is needed because the parallel DFS uses recursive tasks that require larger thread stacks.

> **Note (macOS):** The Makefile uses `g++-15` (Homebrew GCC). If your version differs, update the `CXX` variable in the Makefile (e.g., `g++-14`).

## Sample Output

```
========================================================
    QUANTUM-INSPIRED PARALLEL MAZE SOLVER    
========================================================

[1/4] Generating maze (1001x1001)...
[2/4] Running Sequential DFS (baseline)...
      Sequential DFS completed! Time: 118.256 ms

[3/4] Loading maze data for parallel engine...
[4/4] Running Quantum-Inspired OpenMP Parallel Solver...
      OpenMP parallel solver started. Threads: 10
      Parallel solver found the path! Time: 41.469 ms

========================================================
                 PERFORMANCE REPORT
========================================================
 Sequential DFS Time   : 118.256 ms
 Parallel Solver Time  : 41.469 ms
 SPEEDUP               : 2.85x FASTER
========================================================
```
