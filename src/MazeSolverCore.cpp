#include "MazeSolver.h"
#include <iostream>

using namespace std;

// Constructor: initializes maze dimensions, grid, visited array, and directions
MazeSolver::MazeSolver(int r, int c) {
    rows = r;
    cols = c;

    // All cells start as walls
    maze = vector<vector<int>>(rows, vector<int>(cols, 1));

    // Flat visited array for atomic operations (0 = not visited)
    visited = vector<int>(rows * cols, 0);

    // Default start and end positions
    startX = 1; startY = 1;
    endX = cols - 2; endY = rows - 2;

    // Direction arrays: x = column offset, y = row offset
    dx[0] = 1;   dy[0] = 0;    // right
    dx[1] = -1;  dy[1] = 0;    // left
    dx[2] = 0;   dy[2] = 1;    // down
    dx[3] = 0;   dy[3] = -1;   // up
}

// Loads maze data from an external source into the solver
void MazeSolver::loadMaze(const vector<vector<int>>& mazeData,
                           int sx, int sy, int ex, int ey) {
    maze = mazeData;
    rows = maze.size();
    cols = (rows > 0) ? maze[0].size() : 0;

    // sx = start column, sy = start row (from file format)
    startX = sx;
    startY = sy;
    endX = ex;
    endY = ey;

    // Resize visited array to match new dimensions
    visited = vector<int>(rows * cols, 0);
}

// Main workflow of the maze solver
void MazeSolver::run() {
    cout << "Parallel Quantum-Inspired Maze Solver" << endl;
    cout << "Project structure is ready." << endl;

    cout << "\nCurrent workflow:" << endl;
    cout << "1. Maze generation" << endl;
    cout << "2. Sequential DFS baseline" << endl;
    cout << "3. Parallel candidate preparation" << endl;
    cout << "4. Quantum-inspired ordering" << endl;
    cout << "5. OpenMP parallel search" << endl;
}

// Prints the maze to console with visual symbols
void MazeSolver::printMaze() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (col == startX && row == startY) {
                cout << "S ";
            } else if (col == endX && row == endY) {
                cout << "E ";
            } else if (maze[row][col] == 1) {
                cout << "# ";
            } else if (maze[row][col] == 2) {
                cout << ". ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

// Checks if coordinates are inside the maze boundaries
// x = column, y = row
bool MazeSolver::isInside(int x, int y) {
    return x >= 0 && x < cols && y >= 0 && y < rows;
}

// Checks if a cell is valid: inside, not wall, not visited
bool MazeSolver::isValid(int x, int y) {
    if (!isInside(x, y)) return false;
    if (maze[y][x] == 1) return false;
    if (visited[y * cols + x] != 0) return false;
    return true;
}

// Resets the visited array for a new search
void MazeSolver::resetVisited() {
    visited.assign(rows * cols, 0);
}

// Clears the solution path markers from the maze
void MazeSolver::clearSolution() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 2) {
                maze[i][j] = 0;
            }
        }
    }
}