SFML_PATH = C:/Users/ASUS/SFML-install
SFML_INCLUDE = $(SFML_PATH)/include
SFML_LIB = $(SFML_PATH)/lib
SFML_STATIC = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
LIB = -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -static-libgcc -static-libstdc++

# Include paths
INCLUDES = -Iinclude -Iresource -I$(SFML_INCLUDE)

# Source files
SRC = $(wildcard src/*.cpp) main.cpp

# Object files mapped to obj/ (e.g., src/cell.cpp -> obj/src/cell.o)
OBJ = $(patsubst %.cpp, obj/%.o, $(SRC))

# Output binary
TARGET = main.exe

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	@echo "Linking..."
	g++ -o $@ $^ -L$(SFML_LIB) $(SFML_STATIC) $(LIB)

# Compile rule (create obj/ path if needed)
obj/%.o: %.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	g++ -c $< -o $@ $(INCLUDES) -DSFML_STATIC

# Clean
clean:
	@echo "Cleaning up..."
	del /Q /S obj\*.o 2>nul
	del /Q $(TARGET) 2>nul
	@echo "Cleaned up successfully."
