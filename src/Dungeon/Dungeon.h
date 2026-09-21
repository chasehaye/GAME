#pragma once
#include <string>

class Dungeon
{
public:
    Dungeon();

    void loadFrom(const std::string& filePath);

private:
    std::vector<Room> rooms;
    std::vector<bool> explored;
}