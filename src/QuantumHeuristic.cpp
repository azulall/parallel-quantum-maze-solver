/**
 * @file QuantumHeuristic.cpp
 * @brief Amplitude Amplification ve Heuristic Guidance İmplementasyonu
 */

#include "QuantumHeuristic.h"
#include <cmath>
#include <algorithm>

// Kurucu Fonksiyon: Hedef noktayı sabitleriz
QuantumHeuristic::QuantumHeuristic(int targetX, int targetY) 
    : exitX(targetX), exitY(targetY) {}

// Manhattan Mesafesi Hesaplaması (|x1 - x2| + |y1 - y2|)
double QuantumHeuristic::calculateManhattan(int currentX, int currentY) const {
    return std::abs(currentX - exitX) + std::abs(currentY - exitY);
}

// Genlik Artırma (Amplitude) Mantığı
double QuantumHeuristic::calculateAmplitude(int x, int y) const {
    double distance = calculateManhattan(x, y);
    
    // Eğer hedefe ulaştıysak, maksimum genliği ver (Çıkış burası!)
    if (distance == 0.0) {
        return 999999.0; 
    }

    // Kuantum esintili ağırlıklandırma: 
    // Mesafe azaldıkça genlik (öncelik) eksponansiyel olarak artar.
    return 1.0 / std::sqrt(distance); 
}

// Zülal'in ParallelCandidates.cpp içinden çağıracağı entegrasyon fonksiyonu
void QuantumHeuristic::applyQuantumWeighting(std::vector<PathNode>& candidates) const {
    
    // 1. Her bir aday hücre için süperpozisyon genliğini hesapla
    for (auto& node : candidates) {
        node.amplitude = calculateAmplitude(node.x, node.y);
    }

    // 2. Genlik Artırma (Amplitude Amplification) ilkesi gereği:
    // En yüksek genliğe sahip olan (çıkışa en umut verici) rotayı en başa al.
    // Böylece OpenMP thread'leri önce kaba kuvvet yapmak yerine bu rotalara odaklanacak.
    std::sort(candidates.begin(), candidates.end(), [](const PathNode& a, const PathNode& b) {
        return a.amplitude > b.amplitude;
    });
}
