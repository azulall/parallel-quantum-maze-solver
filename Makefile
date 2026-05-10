CXX = g++-15
CXXFLAGS = -std=c++17 -Wall -Wextra -fopenmp -Iinclude -O2 --sysroot=$(shell xcrun --show-sdk-path)

TARGET = maze

SRC = src/main.cpp \
      src/MazeSolverCore.cpp \
      src/MazeGenerator.cpp \
      src/MazeManager.cpp \
      src/SequentialDfsSolver.cpp \
      src/ParallelCandidates.cpp \
      src/ParallelSolver.cpp \
      src/QuantumHeuristic.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

profile:
	$(CXX) $(CXXFLAGS) -pg $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) gmon.out analysis.txt maze_test.txt solution_seq.txt