#ifndef QUANTUM_HEURISTIC_H
#define QUANTUM_HEURISTIC_H

#include <vector>
#include <cmath>
#include <algorithm>

// Çözücü için basit bir koordinat yapısı
struct Point2D {
    int x;
    int y;
    
    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }
};

// Yön ve o yöne ait kuantum ağırlığını tutacak yapı
struct CandidatePath {
    Point2D pos;
    double amplitudeWeight;

    // Ağırlığı yüksek olanın (hedefe gitme ihtimali yüksek olanın) başa gelmesi için sıralama operatörü
    bool operator<(const CandidatePath& other) const {
        return amplitudeWeight > other.amplitudeWeight; 
    }
};

class QuantumHeuristic {
public:
    // İki nokta arasındaki kuantum esinli ağırlığı hesaplar
    static double calculateAmplitudeWeight(Point2D nextPos, Point2D targetPos, double alpha = 0.5);

    // Bulunulan noktadan gidilebilecek GÜVENLİ yolları ağırlıklarına göre sıralayıp döndürür
    static std::vector<Point2D> getWeightedCandidates(const std::vector<std::vector<int>>& matrix, Point2D current, Point2D target, int PATH_VALUE);
};

#endif
