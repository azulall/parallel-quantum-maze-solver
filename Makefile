CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fopenmp -Iinclude

TARGET = maze

SRC = src/main.cpp \
      src/MazeSolverCore.cpp \
      src/MazeGenerator.cpp \
      src/SequentialSolver.cpp \
      src/ParallelCandidates.cpp \
      src/ParallelSolver.cpp \
      src/QuantumInspired.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

profile:
	$(CXX) $(CXXFLAGS) -pg $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) gmon.out analysis.txt