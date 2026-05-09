#include <vector>
#include "ParallelCandidates.h"


MazeManager mazeManager;
char* filename;

int dx[] = {0, 0, -1, 1}; // right, left, down, up
int dy[] = {-1, 1, 0, 0};


void initializeMaze(char* mazeFileName) {
    filename = mazeFileName;
    mazeManager.getMazeSizeFromFile(filename, n);
    mazeManager.getStartIndicesFromFile(filename, start_x, start_y);
    mazeManager.getEndIndicesFromFile(filename, end_x, end_y);
    mazeManager.getMazeFromFile(filename, maze, n);   
}





bool isValid(std::vector<std::vector<int>>& maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] == 0;
}






std::vector<SearchNode> getParallelCandidates(std::vector<std::vector<int>>& maze, int x, int y, int depth) {
   std::vector<SearchNode> candidates;
   
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (isValid(maze, nx, ny)) {
            SearchNode node = {nx, ny, depth + 1};
            candidates.push_back(node);
        }
    }
    return candidates;
}






std::vector<SearchNode> createInitialFrontier(std::vector<std::vector<int>>& maze,int maxDepth) {
    std::vector<SearchNode> frontier;
    std::vector<SearchNode> queue;
    std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze[0].size(), false));
     
    queue.push_back({start_x, start_y, 0});
    visited[start_x][start_y] = true;

    int head = 0;
    while (head < queue.size()) {
        SearchNode current = queue[head++];
        
        if (current.depth >= maxDepth) {
            frontier.push_back(current);
            continue;
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (isValid(maze, nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                queue.push_back({nx, ny, current.depth + 1});
            }
        }
        
    }
    
    return frontier;
}






bool shouldCreateTask(int depth) {
    return depth > DEPTH_LIMIT;
}
