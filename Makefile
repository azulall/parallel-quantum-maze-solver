CC = gcc
CFLAGS = -O3 -Wall
LDFLAGS = -fopenmp
GEN_SRC = maze_generator.c
GEN_EXE = maze_gen
TEST_DIR = test_cases

all: $(GEN_EXE)

$(GEN_EXE): $(GEN_SRC)
	$(CC) $(CFLAGS) $(GEN_SRC) -o $(GEN_EXE)

run_tests: $(GEN_EXE)
	@mkdir -p $(TEST_DIR)
	@echo "Labirentler üretiliyor..."
	@for n in 21 51 101 501 1001; do \
		for i in $$(seq 1 5); do \
			seed=$$(($$n + $$i)); \
			./$(GEN_EXE) $$n $(TEST_DIR)/maze_$${n}_v$${i}.txt $$seed; \
		done \
	done
	@echo "Tüm testler $(TEST_DIR) klasörüne kaydedildi."

clean:
	rm -f $(GEN_EXE)
	rm -rf $(TEST_DIR)

.PHONY: all run_tests clean