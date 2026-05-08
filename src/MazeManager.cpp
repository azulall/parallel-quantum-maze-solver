#include "MazeManager.h"

// save maze to file in the specified format (.txt)
void MazeManager::saveMazeToFile(std::vector<std::vector<int>> &matrix, int n, int start_x, int start_y, int end_x, int end_y, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == nullptr)
    {
        perror("Failed to open file");
        return;
    }

    fprintf(file, "%d %d\n", n, n); // Write maze dimensions
    fprintf(file, "%d %d\n", start_x, start_y); // Write start point
    fprintf(file, "%d %d\n", end_x, end_y); // Write end point

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}




void MazeManager::getMazeSizeFromFile(const char *filename, int &n) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    int temp_n;

    if (!(file >> n >> temp_n)) {
        std::cerr << "Failed to read maze size from file: " << filename << std::endl;
        n = -1;
    }

    file.close();
}




void MazeManager::getStartIndicesFromFile(const char *filename, int &start_x, int &start_y) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    if (!(file >> start_x >> start_y)) {
        std::cerr << "Failed to read start indices from file: " << filename << std::endl;
        start_x = start_y = -1;
    }

    file.close();
}








void MazeManager::getEndIndicesFromFile(const char *filename, int &end_x, int &end_y) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    std::getline(file, line);

    if (!(file >> end_x >> end_y)) {
        std::cerr << "Failed to read end indices from file: " << filename << std::endl;
        end_x = end_y = -1;
    }

    file.close();
}






void MazeManager::getMazeFromFile(const char *filename, std::vector<std::vector<int>> &matrix, int n)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    matrix.assign(n, std::vector<int>(n));

    std::string line;
    for (int i = 0; i < 3; i++)
    {
        std::getline(file, line);
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!(file >> matrix[i][j])) break;
        }
    }
}








void MazeManager::printMaze(const char *filename, int n)
{
    std::vector<std::vector<int>> matrix;

    getMazeFromFile(filename, matrix, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 0)
                printf("%s", "  ");
            else if (matrix[i][j] == 1)
                printf("%s", "██");
                 else
                printf("%s", "00");
        }
        printf("\n");
    }

    // Clean up
    matrix.clear();
}





