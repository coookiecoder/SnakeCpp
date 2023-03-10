#include <iostream>
#include "Map.h"

#define MAP_SIZE 10

int main() {
    char Input;
    int Frame = 0;

    Map GameMap(MAP_SIZE, 20);
    system("clear");
    GameMap.DisplayMap();

    while (GameMap.GetAlive()) {
        std::cin >> Input;
        switch (Input) {
            case 'w':
                GameMap.NextFrameUp();
                break;
            case 's':
                GameMap.NextFrameDown();
                break;
            case 'd':
                GameMap.NextFrameRight();
                break;
            case 'a':
                GameMap.NextFrameLeft();
                break;
        }
        if (!GameMap.GetAlive()) {
            std::cout << Frame << " frames\n";
        } else {
            system("clear");
            GameMap.DisplayMap();
            Frame = Frame + 1;
        }
    }
    return 0;
}
