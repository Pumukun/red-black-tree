CXX = g++
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

DEBUG_CXXFLAGS = -Wall -I include -g -O0
RELEASE_CXXFLAGS = -Wall -I include -O3

DEBUG_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
DEBUG_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/debug/%.o,$(DEBUG_SOURCES))
RELEASE_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
RELEASE_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/release/%.o,$(RELEASE_SOURCES))

DEBUG_EXECUTABLE = $(BIN_DIR)/RBT_debug
RELEASE_EXECUTABLE = $(BIN_DIR)/RBT_release

all: debug release

debug: $(DEBUG_EXECUTABLE)

$(DEBUG_EXECUTABLE): $(DEBUG_OBJECTS)
	@mkdir -p $(BIN_DIR)/debug
	$(CXX) $(DEBUG_CXXFLAGS) $^ -o $@

$(OBJ_DIR)/debug/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/debug
	$(CXX) $(DEBUG_CXXFLAGS) -c $< -o $@

release: $(RELEASE_EXECUTABLE)

$(RELEASE_EXECUTABLE): $(RELEASE_OBJECTS)
	@mkdir -p $(BIN_DIR)/release
	$(CXX) $(RELEASE_CXXFLAGS) $^ -o $@

$(OBJ_DIR)/release/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/release
	$(CXX) $(RELEASE_CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

