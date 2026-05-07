#include <random>
#include <iostream>
#include <fstream>

#define WALL 1
#define PATH 0

// Point structure to hold edge and inner coordinates
typedef struct
{
    int edge_x, edge_y;
    int in_x, in_y;
} Point;

Point get_random_edge_point(int n);
// shuffle function to randomize the directions
void shuffle(int *array, int n);

// generate maze paths using recursive backtracking DFS algorithm
void generate_paths(int **matrix, int x, int y, int n);

// save maze to file in the specified format (.txt)
void save_maze_to_file(int **matrix, int n, Point start, Point end, const char *filename);

// generate paths with using generate_paths function 
// add the entrance and exit to the maze
// save maze to file with using save_maze_to_file function
void generate_maze(int n, const char *filename);

// read maze information from file
void get_maze_from_file(const char *filename, int **matrix, int n);
void get_maze_size_from_file(const char *filename, int &n);
void get_start_indices_from_file(const char *filename, int &start_x, int &start_y);
void get_end_indices_from_file(const char *filename, int &end_x, int &end_y);

// print maze to console
void print_maze(const char *filename, int n);
