#include "MazeSolver.h"
#include <iostream>
#include <omp.h>

using namespace std;

//OpenMP-based parallel maze solving 
bool MazeSolver::solveParallel() {
    resetVisited();

    bool found = false;

    cout << "OpenMP parallel solver started." << endl;

    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFS(startX, startY, found, 0);
        }
    }

    return found;
}
//Checks and marks a cell as visited in the parallel search
//Prevents multiple threads from visiting the same cell at the same time
bool MazeSolver::tryVisitCell(int x, int y) {
    if (!isInside(x, y) || maze[x][y] == 1) {
        return false;
    }

    bool canVisit = false;

    #pragma omp critical(visited_lock)
    {
        if (!visited[x][y]) {
            visited[x][y] = true;
            canVisit = true;
        }
    }

    return canVisit;
}

//Explores multiple paths using OpenMP task-based parallel DFS
bool MazeSolver::parallelDFS(int x, int y, bool& found, int depth) {
    bool stopSearch = false;

    // check the shared found flag 
    #pragma omp critical(found_lock)
    {
        stopSearch = found;
    }

    if (stopSearch) {
        return true;
    }

    //visit current cell
    if (!tryVisitCell(x, y)) {
        return false;
    }

    // if the exit is reached, update the shared found flag
    if (x == endX && y == endY) {
        #pragma omp critical(found_lock)
        {
            found = true;
        }

        maze[x][y] = 2;
        return true;
    }

    /*

    Planned flow:

    1. Medine's part:
       vector<SearchNode> candidates = getParallelCandidates(x, y, depth);

    2. Kubra's part:
       candidates = orderCandidatesByWeight(candidates);

    3. My part:
       Create OpenMP tasks for candidate branches.

    ex:
    vector<SearchNode> candidates = getParallelCandidates(x, y, depth);
    candidates = orderCandidatesByWeight(candidates);

    for (SearchNode node : candidates) {
        if (shouldCreateTask(node.depth)) {
            #pragma omp task shared(found) firstprivate(node)
            {
                parallelDFS(node.x, node.y, found, node.depth);
            }
        } else {
            parallelDFS(node.x, node.y, found, node.depth);
        }
    }

    #pragma omp taskwait
    */

    return found;
}