#include "MazeSolver.h"
#include <iostream>

using namespace std;

//Constructor: initializes maze size, grid structures, start/end points, and direction arrays
MazeSolver::MazeSolver(int r, int c) {
    rows = r;
    cols = c;

    //all cells are walls
    maze = vector<vector<int>>(rows, vector<int>(cols, 1));

    //no cell is visited at the beginning
    visited = vector<vector<bool>>(rows, vector<bool>(cols, false));

    //start and end points
    startX = 1;
    startY = 1;

    endX = rows - 2;
    endY = cols - 2;

    //direction arrays: right, left, down, up
    dx[0] = 0;   dy[0] = 1;    // right
    dx[1] = 0;   dy[1] = -1;   // left
    dx[2] = 1;   dy[2] = 0;    // down
    dx[3] = -1;  dy[3] = 0;    // up
}

//main workflow of the maze solver
void MazeSolver::run() {
    cout << "Parallel Quantum-Inspired Maze Solver" << endl;
    cout << "Project structure is ready." << endl;

    cout << "\nCurrent workflow:" << endl;
    cout << "1. Maze generation" << endl;
    cout << "2. Sequential DFS baseline" << endl;
    cout << "3. Parallel candidate preparation" << endl;
    cout << "4. Quantum-inspired ordering" << endl;
    cout << "5. OpenMP parallel search" << endl;

    cout << "\nMaze generation and solver modules will be integrated step by step." << endl;

    /*
    
    generateMaze();

    cout << "\nGenerated Maze:\n";
    printMaze();

    bool sequentialFound = solveSequential();

    if (sequentialFound) {
        cout << "\nSequential DFS found a path.\n";
    } else {
        cout << "\nSequential DFS could not find a path.\n";
    }

    printMaze();

    clearSolution();
    resetVisited();

    bool parallelFound = solveParallel();

    if (parallelFound) {
        cout << "\nParallel solver found a path.\n";
    } else {
        cout << "\nParallel solver could not find a path.\n";
    }
    */
}

//Prints the maze to the console
void MazeSolver::printMaze() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == startX && j == startY) {
                cout << "S ";
            } else if (i == endX && j == endY) {
                cout << "E ";
            } else if (maze[i][j] == 1) {
                cout << "# ";
            } else if (maze[i][j] == 2) {
                cout << ". ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

//Checks if coordinates are inside the maze
bool MazeSolver::isInside(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

//Checks if cell is valid for movement
bool MazeSolver::isValid(int x, int y) {
    return isInside(x, y) && maze[x][y] != 1 && !visited[x][y];
}

//Resets visited array for another search
void MazeSolver::resetVisited() {
    visited = vector<vector<bool>>(rows, vector<bool>(cols, false));
}

//Clears the previously marked solution path before running another 
void MazeSolver::clearSolution() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 2) {
                maze[i][j] = 0;
            }
        }
    }
}