#ifndef PARALLEL_CANDIDATES_H
#define PARALLEL_CANDIDATES_H

#include <vector>
#include "MazeManager.h"

struct SearchNode {
    int x, y;
    int depth;
};

const int DEPTH_LIMIT = 20;
int n, start_x, start_y, end_x, end_y;
std::vector<std::vector<int>> maze;

void initializeMaze(char* mazeFileName);

bool isValid(std::vector<std::vector<int>>& maze, int x, int y);


std::vector<SearchNode> getParallelCandidates(std::vector<std::vector<int>>& maze, int x, int y, int depth);

std::vector<SearchNode> createInitialFrontier(std::vector<std::vector<int>>& maze, int maxDepth);

bool shouldCreateTask(int depth);

#endif
