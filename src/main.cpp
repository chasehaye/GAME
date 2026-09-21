#include <iostream>

int main() {

    bool running = true;
    std::cout << "Welcome to my game made for learning\n";
    while(running) {
        std::cout << "Enter a command (q to quit): ";

        char input;
        std::cin >> input;
        
        if (input == 'q')
        {
            running = false;
        }

        std::cout << "Game updated.\n";
    }

    return 0;
}