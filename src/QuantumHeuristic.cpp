#include "QuantumHeuristic.h"
#include <cmath>
#include <algorithm>


// Labirentin çıkış (hedef) koordinatlarını sisteme tanıtır.
QuantumHeuristic::QuantumHeuristic(int targetX, int targetY) 
    : exitX(targetX), exitY(targetY) {}

// Sezgisel Rehberlik (Heuristic Guidance)
// Manhattan mesafesi kullanarak hedefe olan uzaklığı ölçer.
double QuantumHeuristic::calculateManhattan(int currentX, int currentY) const {
    // Formül: |x1 - x2| + |y1 - y2|
    return std::abs(currentX - exitX) + std::abs(currentY - exitY);
}


// Kuantum Genlik (Amplitude) Hesaplama
// Kuantum dalga fonksiyonundan ilham alınarak mesafeyi bir genliğe çevirir.
double QuantumHeuristic::calculateAmplitude(int x, int y) const {
    double distance = calculateManhattan(x, y);
    
    // Eğer hedef hücredeysek, maksimum genliği döndür (kesin çözüm)
    if (distance == 0.0) {
        return 999999.0; 
    }

    // Kuantum Esintili Ağırlıklandırma Formülü:
    // Mesafe azaldıkça genlik (çözüm olasılığı) artar. 
    // 1 / sqrt(distance) formülü ile hedefe yakın yolların önceliği katlanarak artırılır.
    return 1.0 / std::sqrt(distance); 
}

// ---------------------------------------------------------
// Genlik Artırma ve Sıralama (Amplitude Amplification & Sort)
// Zülal'in paralel task motoru (OpenMP) tarafından çağrılacak ana fonksiyondur.
// ---------------------------------------------------------
void QuantumHeuristic::applyQuantumWeighting(std::vector<PathNode>& candidates) const {
    
    // 1. Aşama: Süperpozisyon (Superposition) Durumu
    // Her bir aday hücre için genlik değerlerini hesapla ve ata.
    for (auto& node : candidates) {
        node.amplitude = calculateAmplitude(node.x, node.y);
    }

    // 2. Aşama: Genlik Artırma (Amplitude Amplification)
    // Adayları genlik değerlerine göre büyükten küçüğe sırala.
    // Böylece en yüksek olasılıklı (en umut verici) yollar listenin başına geçer.
    std::sort(candidates.begin(), candidates.end(), [](const PathNode& a, const PathNode& b) {
        return a.amplitude > b.amplitude; // Büyük olan başa gelir
    });
}
