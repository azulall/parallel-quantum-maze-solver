#ifndef QUANTUM_HEURISTIC_H
#define QUANTUM_HEURISTIC_H

#include <vector>
#include <cmath>
#include <algorithm>

// Simple coordinate structure for the solver
struct Point2D {
    int x;  // column
    int y;  // row

    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }
};

// Candidate path with its quantum-inspired amplitude weight
struct CandidatePath {
    Point2D pos;
    double amplitudeWeight;

    // Higher weight = closer to exit = explored first
    bool operator<(const CandidatePath& other) const {
        return amplitudeWeight > other.amplitudeWeight;
    }
};

class QuantumHeuristic {
public:
    // Calculates quantum-inspired amplitude weight between two points
    // Uses inverse sqrt of Manhattan distance (Grover's amplification idea)
    static double calculateAmplitudeWeight(Point2D nextPos, Point2D targetPos);

    // Returns valid neighbor positions sorted by quantum weight (best first)
    static std::vector<Point2D> getWeightedCandidates(
        const std::vector<std::vector<int>>& matrix,
        Point2D current, Point2D target, int PATH_VALUE);
};

#endif
