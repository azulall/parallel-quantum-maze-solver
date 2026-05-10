#include "MazeSolver.h"
#include <vector>

// Finds valid neighboring cells that can be explored from position (x, y)
// Returns them as SearchNode objects with incremented depth
// x = column, y = row
std::vector<SearchNode> MazeSolver::getParallelCandidates(int x, int y, int depth) {
    std::vector<SearchNode> candidates;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny)) {
            SearchNode node;
            node.x = nx;
            node.y = ny;
            node.depth = depth + 1;
            candidates.push_back(node);
        }
    }

    return candidates;
}

// Creates an initial frontier of search nodes using BFS from the start
// Expands up to maxDepth levels to distribute early work among threads
std::vector<SearchNode> MazeSolver::createInitialFrontier(int maxDepth) {
    std::vector<SearchNode> frontier;
    std::vector<SearchNode> queue;
    std::vector<std::vector<bool>> bfsVisited(rows, std::vector<bool>(cols, false));

    queue.push_back({startX, startY, 0});
    bfsVisited[startY][startX] = true;

    int head = 0;
    while (head < (int)queue.size()) {
        SearchNode current = queue[head++];

        // Nodes at max depth become the frontier for parallel tasks
        if (current.depth >= maxDepth) {
            frontier.push_back(current);
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isInside(nx, ny) && maze[ny][nx] != 1 && !bfsVisited[ny][nx]) {
                bfsVisited[ny][nx] = true;
                queue.push_back({nx, ny, current.depth + 1});
            }
        }
    }

    return frontier;
}

// Decides whether a new OpenMP task should be created at this depth
// Tasks are created at SHALLOW depths to enable parallelism
// At deeper levels, search continues sequentially to avoid overhead
bool MazeSolver::shouldCreateTask(int depth) {
    return depth < TASK_DEPTH_LIMIT;
}
