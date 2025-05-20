# SFML settings
SFML_PATH = C:/Users/ASUS/SFML-install
SFML_INCLUDE = $(SFML_PATH)/include
SFML_LIB = $(SFML_PATH)/lib
SFML_STATIC = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s

# Additional libraries for Windows static linking
LIB = -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -static-libgcc -static-libstdc++

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g -DSFML_STATIC $(INCLUDES)

# Include paths
INCLUDES = -Iinclude -Iresource -I$(SFML_INCLUDE)

# Source and object files
SRC = $(wildcard src/*.cpp) main.cpp
OBJ = $(patsubst %.cpp, obj/%.o, $(SRC))

# Target binary
TARGET = minesweeper.exe

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJ)
	@echo Linking...
	$(CXX) -o $@ $^ -L$(SFML_LIB) $(SFML_STATIC) $(LIB)

# Compile each source file into object file
obj/%.o: %.cpp
	@echo Compiling $<...
	@mkdir "$(dir $@)" 2>nul || exit 0
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean rule
clean:
	@echo Cleaning up...
	@if exist obj rmdir /S /Q obj
	@del /Q $(TARGET) 2>nul || exit 0
	@echo Done.
