#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>

#define WALL 1
#define PATH 0

typedef struct
{
    int edge_x, edge_y;
    int in_x, in_y;
} Point;

Point get_random_edge_point(int n);
void shuffle(int *array, int n);
void generate_maze(int **matrix, int x, int y, int n);
void save_maze_to_file(int **matrix, int n, Point start, Point end, const char *filename);

#endif