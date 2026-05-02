// QuantumSolver.cpp
// Author: Medine Merve Maral

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <omp.h>
#include <cstdint>

class QuantumSolver {
private:
    int n;
    int startX, startY, endX, endY;
    std::vector<char> grid; // '0' for path, '1' for wall
    uint8_t* amplitudes; // Amplitudes for each cell, 0 or 1 for simplicity
    uint8_t* visited; // Visited flag for each cell, 0 or 1

    inline long getIdx(int x, int y) { return (long)y * n + x; }

public:
    QuantumSolver() : amplitudes(nullptr), visited(nullptr) {}

    ~QuantumSolver() {
        delete[] amplitudes;
        delete[] visited; 
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        if (!(file >> n >> startX >> startY >> endX >> endY)) return false;

        long totalSize = (long)n * n;
        grid.resize(totalSize);
        amplitudes = new uint8_t[totalSize]();
        visited = new uint8_t[totalSize](); 

        // Turn the martix data into a single string for easier access
        for (int i = 0; i < n; ++i) {
            std::string line;
            if (!(file >> line)) break;
            for (int j = 0; j < n; ++j) {
                grid[getIdx(j, i)] = line[j];
            }
        }

        return true;
    }

    void solve() {
        long startIdx = getIdx(startX, startY);
        long targetIdx = getIdx(endX, endY);
        
        amplitudes[startIdx] = 1;
        std::vector<int> activeIndices; // Keeps track of currently active indices (non-zero amplitude)
        activeIndices.push_back((int)startIdx); // Start with the initial position
        visited[startIdx] = 1; // Mark the start cell as visited

        int maxSteps = n * n;
        bool found = false;
        double startTime = omp_get_wtime();

        for (int step = 0; step < maxSteps; ++step) {
            if (activeIndices.empty()) break;

            // Target check
            if (visited[targetIdx]) {
                std::cout << "Target reached at step: " << step << std::endl;
                found = true;
                break;
            }

            int max_threads = omp_get_max_threads(); // Get the maximum number of threads available
            std::vector<std::vector<int>> threadNext(max_threads); // Each thread will have its own vector to store next active indices
            
            #pragma omp parallel
            {
                int tid = omp_get_thread_num(); // Get the thread ID for indexing threadNext
                
                #pragma omp for nowait // Distribute the loop iterations among threads without waiting at the end of the loop
                for (long i = 0; i < (long)activeIndices.size(); ++i) {
                    int currIdx = activeIndices[i];
                    int x = currIdx % n;  // Calculate x and 
                    int y = currIdx / n; //  y from the index

                    // Check neighbors (up, down, left, right)
                    const int dx[] = {0, 0, -1, 1};
                    const int dy[] = {-1, 1, 0, 0};

                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];

                         // Check bounds and if it's a path
                        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                            int nIdx = (int)getIdx(nx, ny);
                            // If it's a path and not visited, add to next active indices
                            if (grid[nIdx] == '0' && !visited[nIdx]) {
                                // Update visited atomically
                                if (__sync_bool_compare_and_swap(&visited[nIdx], 0, 1)) {
                                    /*__sync_bool_compare_and_swap, if visited is 0, set it to 1.
                                    it is a lock-free, atomic operation. */
                                    threadNext[tid].push_back(nIdx);
                                }
                            }
                        }
                    }
                }
            }

            // Combine results from all threads into activeIndices for the next iteration
            activeIndices.clear();
            for (int i = 0; i < max_threads; ++i) {
                activeIndices.insert(activeIndices.end(), threadNext[i].begin(), threadNext[i].end());
                // add from the end of activeIndices to avoid unnecessary copying
            }
        }

        double endTime = omp_get_wtime();
        if (!found) std::cout << "Target not found! The path might be blocked." << std::endl;
        std::cout << "Time: " << (endTime - startTime) << " s." << std::endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    QuantumSolver solver;
    if (solver.loadFromFile(argv[1])) solver.solve();
    return 0;
}