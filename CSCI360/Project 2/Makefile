# all: sim
# sim:
# 	g++ -Wall -std=c++11 -o proj2 main.cpp Robot.cpp Project2.cpp AStar.o
# State.o: State.h State.cpp
# 	g++ -Wall -c State.cpp -o State.o
# AStar.o: AStar.cpp AStar.h
# 	g++ -Wall -c AStar.cpp -o AStar.o
# testfile:
# 	g++ -Wall -std=c++11 -o testfile test.cpp Robot.cpp AStar.o
# clean:
# 	rm proj2
# 	rm AStar.o
# 	rm State.o
# 	rm testfile

BIN_DIR = bin
SRC_DIR = src
CXX = g++
CPPFLAGS = -Wall -g -std=c++11 -fdiagnostics-color
VALGRIND = valgrind --tool=memcheck --leak-check=yes
TARGETS = $(BIN_DIR)/Test.o $(BIN_DIR)/Project2.o $(BIN_DIR)/State.o $(BIN_DIR)/AStar.o $(BIN_DIR)/PriorityQueue.o $(BIN_DIR)/Robot.o
#GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(TARGETS)

test: test

sim: sim

# Compiles any .o file by using the .cpp and .h file of the same name. 
$(BIN_DIR)/%.o: %.cpp %.h $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

sim: main.cpp $(TARGETS)
	$(CXX) $(CPPFLAGS) $^ -o $@ -lm

test: main_test.cpp $(TARGETS)
	$(CXX) $(CPPFLAGS) $^ -o $@ -lm

.PHONY: runtest
grind_llisttest: test
	-$(VALGRIND) ./test
	-@echo "--- All Tested!---"
	
.PHONY: clean
clean:
	rm sim
	rm -rf sim.dSYM
	rm -rf $(BIN_DIR) main

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp