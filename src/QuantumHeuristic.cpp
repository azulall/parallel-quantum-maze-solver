#include "QuantumHeuristic.h"
#include "MazeSolver.h"
#include <cmath>
#include <algorithm>

// Calculates quantum-inspired weight for a candidate position
// Simulates Grover's amplitude amplification concept:
// positions closer to exit receive higher amplitude (priority)
double QuantumHeuristic::calculateAmplitudeWeight(Point2D nextPos, Point2D targetPos) {
    // Manhattan distance to the exit
    double distance = std::abs(nextPos.x - targetPos.x) +
                      std::abs(nextPos.y - targetPos.y);

    // If we are at the target, return maximum weight (certain solution)
    if (distance == 0.0) {
        return 999999.0;
    }

    // Quantum-inspired formula: 1 / sqrt(distance)
    // As distance decreases, amplitude increases non-linearly
    // This mimics how Grover's algorithm amplifies correct solutions
    return 1.0 / std::sqrt(distance);
}

// Returns valid neighboring cells sorted by quantum amplitude weight
// Best candidates (closest to target) appear first in the list
std::vector<Point2D> QuantumHeuristic::getWeightedCandidates(
    const std::vector<std::vector<int>>& matrix,
    Point2D current, Point2D target, int PATH_VALUE) {

    // Direction offsets: right, left, down, up
    int ddx[] = {1, -1, 0, 0};
    int ddy[] = {0, 0, 1, -1};

    int numRows = matrix.size();
    int numCols = (numRows > 0) ? (int)matrix[0].size() : 0;

    std::vector<CandidatePath> candidates;

    for (int i = 0; i < 4; i++) {
        int nx = current.x + ddx[i];
        int ny = current.y + ddy[i];

        // Check bounds and if the cell is a valid path
        if (nx >= 0 && nx < numCols && ny >= 0 && ny < numRows
            && matrix[ny][nx] == PATH_VALUE) {
            CandidatePath cp;
            cp.pos = {nx, ny};
            cp.amplitudeWeight = calculateAmplitudeWeight(cp.pos, target);
            candidates.push_back(cp);
        }
    }

    // Sort by amplitude weight (highest first = most promising)
    std::sort(candidates.begin(), candidates.end());

    // Extract sorted positions
    std::vector<Point2D> result;
    for (auto& cp : candidates) {
        result.push_back(cp.pos);
    }
    return result;
}

// ---- MazeSolver quantum integration methods ----

// Calculates the quantum-inspired weight for a search node
double MazeSolver::calculateWeight(const SearchNode& node) {
    Point2D nodePos = {node.x, node.y};
    Point2D targetPos = {endX, endY};
    return QuantumHeuristic::calculateAmplitudeWeight(nodePos, targetPos);
}

// Sorts candidate nodes by their quantum weight (most promising first)
// Implements the "amplitude amplification" ordering concept
std::vector<SearchNode> MazeSolver::orderCandidatesByWeight(std::vector<SearchNode> candidates) {
    std::vector<std::pair<double, SearchNode>> weighted;
    for (auto& node : candidates) {
        double w = calculateWeight(node);
        weighted.push_back({w, node});
    }

    // Sort by weight descending (highest amplitude first)
    std::sort(weighted.begin(), weighted.end(),
        [](const std::pair<double, SearchNode>& a,
           const std::pair<double, SearchNode>& b) {
            return a.first > b.first;
        });

    std::vector<SearchNode> result;
    for (auto& p : weighted) {
        result.push_back(p.second);
    }
    return result;
}
