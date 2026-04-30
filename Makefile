CXX=g++

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
BIN_NAME = main

OBJ_DIR = $(BIN_DIR)/obj

CXXFLAGS=-I$(INC_DIR) -std=c++17 -Wall -Wextra -g

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BIN  = $(BIN_DIR)/$(BIN_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

build: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $(BIN) $^ $(CXXFLAGS)

clean:
	rm -Rf $(OBJ_DIR)/*
	find $(BIN_DIR) -maxdepth 1 -type f -delete

run: build
	./$(BIN)

.PHONY: build clean run