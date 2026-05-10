#include "MazeSolver.h"
#include <iostream>
#include <omp.h>

using namespace std;

// OpenMP-based parallel maze solving entry point
// Uses task-based parallelism with quantum-inspired path ordering
bool MazeSolver::solveParallel() {
    resetVisited();

    bool found = false;

    cout << "OpenMP parallel solver started. Threads: "
         << omp_get_max_threads() << endl;

    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFS(startX, startY, found, 0);
        }
    }

    return found;
}

// Atomically checks and marks a cell as visited
// Uses atomic capture for lock-free thread safety
// Returns true if this thread is the first to visit the cell
bool MazeSolver::tryVisitCell(int x, int y) {
    if (!isInside(x, y) || maze[y][x] == 1) {
        return false;
    }

    int idx = y * cols + x;
    int oldVal;

    // Atomic capture: read old value and set to 1 in one operation
    // This replaces the expensive critical section for much better performance
    #pragma omp atomic capture
    {
        oldVal = visited[idx];
        visited[idx] = 1;
    }

    // If old value was 0, we are the first thread to visit this cell
    return oldVal == 0;
}

// Parallel DFS: explores maze paths using OpenMP tasks
// At shallow depths, creates new tasks for each candidate branch
// At deeper depths, continues sequentially within the current task
// Quantum-inspired ordering ensures most promising paths are tried first
bool MazeSolver::parallelDFS(int x, int y, bool& found, int depth) {
    // Early termination: another thread already found the exit
    if (found) return true;

    // Try to claim this cell atomically
    if (!tryVisitCell(x, y)) {
        return false;
    }

    // Check if we reached the exit
    if (x == endX && y == endY) {
        #pragma omp critical(found_lock)
        {
            found = true;
        }
        maze[y][x] = 2;
        return true;
    }

    // Step 1: Get valid neighboring cells (Medine's parallel candidates)
    std::vector<SearchNode> candidates = getParallelCandidates(x, y, depth);

    // Step 2: Sort by quantum-inspired weights (Kubra's quantum ordering)
    // Most promising paths (closer to exit) are explored first
    candidates = orderCandidatesByWeight(candidates);

    // Step 3: Explore candidates with OpenMP tasks (Zulal's parallel engine)
    for (const auto& node : candidates) {
        if (found) break;

        if (shouldCreateTask(node.depth)) {
            // Create a new OpenMP task for this branch
            #pragma omp task shared(found) firstprivate(node)
            {
                if (!found) {
                    parallelDFS(node.x, node.y, found, node.depth);
                }
            }
        } else {
            // Continue sequentially within this task to avoid overhead
            parallelDFS(node.x, node.y, found, node.depth);
        }
    }

    // Wait for all child tasks to complete before returning
    #pragma omp taskwait

    return found;
}