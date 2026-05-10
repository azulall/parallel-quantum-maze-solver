#include <iostream>
#include <chrono>
#include <vector>

// Takımın yazdığı tüm modüller
#include "MazeGenerator.h"
#include "MazeManager.h"
#include "SequentialDfsSolver.h"
#include "MazeSolver.h" // Zülal'in paralel çözücüsü

using namespace std;
using namespace std::chrono;

int main() {
    // 1. Ayarlar ve Labirent Boyutu
    // Farkı net görebilmek için labirenti büyük tutmak önemlidir (örn: 1001x1001)
    int n = 1001; 
    const char* mazeFile = "maze_test.txt";
    const char* seqSolutionFile = "solution_seq.txt";
    
    cout << "========================================================\n";
    cout << "    TEKNOFEST KUANTUM ESINLI PARALEL LABIRENT COZUCU    \n";
    cout << "========================================================\n\n";

    // 2. Labirent Üretimi (MazeGenerator)
    cout << "[1/4] Labirent uretiliyor (" << n << "x" << n << ")...\n";
    MazeGenerator generator;
    generator.generateMaze(n, mazeFile);
    cout << "      Labirent basariyla '" << mazeFile << "' dosyasina kaydedildi.\n\n";

    // 3. Klasik DFS (Sequential) Çözümü ve Süre Ölçümü
    cout << "[2/4] Klasik Ardisil (Sequential) DFS calistiriliyor...\n";
    SequentialDfsSolver seqSolver;
    
    // Kronometreyi başlat
    auto start_seq = high_resolution_clock::now();
    seqSolver.solveMazeWithSeqDfs(mazeFile, seqSolutionFile);
    auto end_seq = high_resolution_clock::now(); // Kronometreyi durdur
    
    duration<double, std::milli> seq_time = end_seq - start_seq;
    cout << "      Klasik DFS Tamamlandi! Sure: " << seq_time.count() << " ms\n\n";

    // 4. Paralel Motor İçin Dosyadan Verileri Okuma (MazeManager)
    cout << "[3/4] Paralel motor icin labirent verileri yukleniyor...\n";
    MazeManager manager;
    int size_n, startX, startY, endX, endY;
    vector<vector<int>> mazeMatrix;
    
    manager.getMazeSizeFromFile(mazeFile, size_n);
    manager.getStartIndicesFromFile(mazeFile, startX, startY);
    manager.getEndIndicesFromFile(mazeFile, endX, endY);
    manager.getMazeFromFile(mazeFile, mazeMatrix, size_n);

    // 5. Kuantum Esinli OpenMP Paralel Çözümü ve Süre Ölçümü
    cout << "[4/4] Kuantum Esinli OpenMP Paralel Motor calistiriliyor...\n";
    
    MazeSolver parSolver(size_n, size_n); 
    
    // ENTEGRASYON NOTU: Zülal'in MazeSolver sınıfında bu değişkenler 'public' 
    // olmalı veya bunları set eden bir fonksiyon (örn: loadMaze) bulunmalıdır.
    // parSolver.maze = mazeMatrix; 
    // parSolver.startX = startX; parSolver.startY = startY;
    // parSolver.endX = endX; parSolver.endY = endY;

    // Kronometreyi başlat
    auto start_par = high_resolution_clock::now();
    bool isFound = parSolver.solveParallel(); 
    auto end_par = high_resolution_clock::now(); // Kronometreyi durdur
    
    duration<double, std::milli> par_time = end_par - start_par;
    
    if (isFound) {
        cout << "      Kuantum Paralel Tamamlandi! Sure: " << par_time.count() << " ms\n\n";
    } else {
        cout << "      UYARI: Paralel motor yol bulamadi!\n\n";
    }

    // 6. Sonuç ve Hızlanma (Speedup) Raporu
    cout << "========================================================\n";
    cout << "                   PERFORMANS RAPORU                    \n";
    cout << "========================================================\n";
    cout << " Klasik DFS Suresi     : " << seq_time.count() << " ms\n";
    cout << " Kuantum Paralel Suresi: " << par_time.count() << " ms\n";
    
    if (par_time.count() > 0) {
        double speedup = seq_time.count() / par_time.count();
        cout << " HIZ ARTISI (SPEEDUP)  : " << speedup << " KAT DAHA HIZLI!\n";
    }
    cout << "========================================================\n";

    return 0;
}
