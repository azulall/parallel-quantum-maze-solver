#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include "MazeManager.h"

#define WALL 1
#define PATH 0

class MazeGenerator
{
public:
        typedef struct
        {
            int edge_x, edge_y;
            int in_x, in_y;
        } Point;

    Point getRandomEdgePoint(int n);
    // shuffle function to randomize the directions
    void shuffle(int *array, int n);

    // generate maze paths using recursive backtracking DFS algorithm
    void generatePaths(std::vector<std::vector<int>> &matrix, int x, int y, int n);

    // generate paths with using generate_paths function
    // add the entrance and exit to the maze
    // save maze to file with using saveMazeToFile function
    void generateMaze(int n, const char *filename);

};

#endif
