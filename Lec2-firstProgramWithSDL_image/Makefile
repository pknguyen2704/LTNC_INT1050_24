SRC_DIR = src
BUILD_DIR = build
CC = clang++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play
INCLUDE_PATHS = -I include/SDL2 -I include/SDL2_image
#LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.26.2/lib/
LIBRARY_PATHS = -L lib/SDL2 -L lib/SDL2_image
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g
LINKER_FLAGS = -lsdl2 -lsdl2_image

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)