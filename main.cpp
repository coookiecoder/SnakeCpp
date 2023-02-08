#include <iostream>
#include "Map.h"

int main() {
    char Input;
    int Frame = 0;

    Map GameMap(10, 5);
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
        GameMap.DisplayMap();
    }
    return 0;
}
