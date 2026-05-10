#include "MazeGenerator.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stack>

MazeGenerator::Point MazeGenerator::getRandomEdgePoint(int n)
{
    MazeGenerator::Point p;
    int edge = rand() % 4; // 0: up, 1: down, 2: left, 3: right

    int rand_pos = 1 + 2 * (rand() % ((n - 1) / 2));

    switch (edge)
    {
    case 0: // up
        p.edge_x = rand_pos;
        p.edge_y = 0;
        p.in_x = rand_pos;
        p.in_y = 1;
        break;
    case 1: // down
        p.edge_x = rand_pos;
        p.edge_y = n - 1;
        p.in_x = rand_pos;
        p.in_y = n - 2;
        break;
    case 2: // left
        p.edge_x = 0;
        p.edge_y = rand_pos;
        p.in_x = 1;
        p.in_y = rand_pos;
        break;
    case 3: // right
        p.edge_x = n - 1;
        p.edge_y = rand_pos;
        p.in_x = n - 2;
        p.in_y = rand_pos;
        break;
    default:
        break;
    }
    return p;
}

// shuffle function to randomize the directions
void MazeGenerator::shuffle(int *array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

// Iterative version of recursive backtracking maze generation
// Uses an explicit stack to avoid stack overflow on large mazes (e.g. 1001x1001)
void MazeGenerator::generatePaths(std::vector<std::vector<int>> &matrix, int x, int y, int n)
{
    // Each stack frame stores: current position and which direction index to try next
    struct Frame {
        int x, y;
        int dirs[4];
        int dirIdx;
    };

    std::stack<Frame> callStack;

    // Push initial frame
    Frame first;
    first.x = x;
    first.y = y;
    first.dirs[0] = 0; first.dirs[1] = 1; first.dirs[2] = 2; first.dirs[3] = 3;
    shuffle(first.dirs, 4);
    first.dirIdx = 0;
    callStack.push(first);

    while (!callStack.empty()) {
        Frame &cur = callStack.top();

        if (cur.dirIdx >= 4) {
            // All directions tried, backtrack
            callStack.pop();
            continue;
        }

        int dir = cur.dirs[cur.dirIdx];
        cur.dirIdx++;

        int ddx = 0, ddy = 0;
        if (dir == 0) ddy = -2;      // Up
        else if (dir == 1) ddy = 2;  // Down
        else if (dir == 2) ddx = -2; // Left
        else if (dir == 3) ddx = 2;  // Right

        int nx = cur.x + ddx;
        int ny = cur.y + ddy;

        if (nx >= 0 && nx < n && ny >= 0 && ny < n && matrix[ny][nx] == WALL)
        {
            matrix[cur.y + ddy / 2][cur.x + ddx / 2] = PATH;
            matrix[ny][nx] = PATH;

            // Push new frame for the neighbor cell
            Frame next;
            next.x = nx;
            next.y = ny;
            next.dirs[0] = 0; next.dirs[1] = 1; next.dirs[2] = 2; next.dirs[3] = 3;
            shuffle(next.dirs, 4);
            next.dirIdx = 0;
            callStack.push(next);
        }
    }
}

// Main function to generate maze with entrance and exit, then save to file
void MazeGenerator::generateMaze(int n, const char *filename)
{
    srand((unsigned)time(NULL));

    MazeManager manager;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, WALL));

    MazeGenerator::Point start = getRandomEdgePoint(n);
    MazeGenerator::Point end;
    do
    {
        end = getRandomEdgePoint(n);
    } while (start.edge_x == end.edge_x && start.edge_y == end.edge_y);

    // Open entrance and generate maze paths
    matrix[start.in_y][start.in_x] = PATH;
    generatePaths(matrix, start.in_x, start.in_y, n);

    // Open entrance and exit on the edges
    matrix[start.edge_y][start.edge_x] = PATH;
    matrix[end.edge_y][end.edge_x] = PATH;
    matrix[end.in_y][end.in_x] = PATH;

    manager.saveMazeToFile(matrix, n, start.edge_x, start.edge_y, end.edge_x, end.edge_y, filename);

    matrix.clear();
}
