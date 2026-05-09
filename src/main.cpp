#include "MazeSolver.h"

int main() {
    //ex:20x20 maze solver object
    MazeSolver solver(20, 20);

    //start the main workflow
    solver.run();

    return 0;
}