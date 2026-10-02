CXX = g++

CXXFLAGS = -std=c++20 -Wall -Wextra -Isrc

# raylib plus the Windows system libraries it draws and plays sound through.
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = build/game.exe

# Every .cpp under src/ (up to two folders deep, e.g. src/world/map/) is compiled,
# so new files need no Makefile edit. Nesting deeper needs another src/*/*/*/ pattern.
SRC = $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp)
HDR = $(wildcard src/*/*.h src/*/*/*.h)

$(TARGET): $(SRC) $(HDR)
	if not exist build mkdir build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDLIBS)

run: $(TARGET)
	.\$(subst /,\,$(TARGET))

clean:
	if exist build rmdir /s /q build

help:
	@echo Available commands:
	@echo   make       Build the game
	@echo   make run   Build and run the game
	@echo   make clean Remove build files
	@echo   make help  Show this help message
