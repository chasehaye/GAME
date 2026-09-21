CXX = g++

CXXFLAGS = -std=c++20 -Wall -Wextra

TARGET = build/game.exe

SRC = src/main.cpp \
      src/Game/Game.cpp \
      src/Player/Player.cpp \

$(TARGET): $(SRC)
	if not exist build mkdir build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	.\$(TARGET)

clean:
	if exist build rmdir /s /q build

help:
	@echo Available commands:
	@echo   make       Build the game
	@echo   make run   Build and run the game
	@echo   make clean Remove build files
	@echo   make help  Show this help message