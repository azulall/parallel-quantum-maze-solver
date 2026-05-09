#ifndef MAZEMANAGER_H
#define MAZEMANAGER_H

#include <vector>
#include <random>
#include <iostream>
#include <fstream>

class MazeManager
{
public:
    // save maze to file in the specified format (.txt)
    void saveMazeToFile(std::vector<std::vector<int>> &matrix, int n, int start_x, int start_y, int end_x, int end_y, const char *filename);

    // read maze information from file
    void getMazeFromFile(const char *filename, std::vector<std::vector<int>> &matrix, int n);
    void getMazeSizeFromFile(const char *filename, int &n);
    void getStartIndicesFromFile(const char *filename, int &start_x, int &start_y);
    void getEndIndicesFromFile(const char *filename, int &end_x, int &end_y);

    // print maze to console
    void printMaze(const char *filename, int n);
};

#endif
