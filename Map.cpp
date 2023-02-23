#include <random>
#include <iostream>
#include "Map.h"

#define APPLE_DATA 1
#define MAX_SPAWN_TRY 1000

Map::Map(int Size, int AppleNumber) {
    if (Size * Size <= (AppleNumber - 6)) {
        return;
    }
    int HeadLocationX;
    int HeadLocationY;
    int AppleLocationX;
    int AppleLocationY;

    MapSize = Size;

    AppleMap = (int *) malloc(Size * Size * sizeof(int));
    SnakeMap = (int *) malloc(Size * Size * sizeof(int));
    if (AppleMap == nullptr || SnakeMap == nullptr) {
        exit(-1);
    }

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            SetSnakeMapData(x, y, 0);
        }
    }

    HeadLocationX = (int) random() % Size;
    HeadLocationY = (int) random() % Size;
    *(SnakeMap + HeadLocationX * Size + HeadLocationY) = 1;

    for (int Iteration = 0; Iteration < AppleNumber; Iteration++) {
        AppleLocationX = (int) random() % Size;
        AppleLocationY = (int) random() % Size;
        if (AppleLocationX == HeadLocationX && AppleLocationY == HeadLocationY) {
            Iteration--;
        } else if (GetAppleMapData(AppleLocationX, AppleLocationY)) {
            Iteration--;
        } else {
            SetAppleMapData(AppleLocationX,AppleLocationY,APPLE_DATA);
        }
    }

    Alive = true;
    SnakeLength = 5;
}

int Map::GetAppleMapData(int x, int y) {
    return *(AppleMap + y * MapSize + x);
}

int Map::GetSnakeMapData(int x, int y) {
    return *(SnakeMap + y * MapSize + x);
}

void Map::SetAppleMapData(int x, int y, int value) {
    *(AppleMap + y * MapSize + x) = value;
}

void Map::SetSnakeMapData(int x, int y, int value) {
    *(SnakeMap + y * MapSize + x) = value;
}

bool Map::GetAlive() {
    return Alive;
}


void Map::NextFrameUp() {
    int SpawnTry;
    int AppleLocationX;
    int AppleLocationY;
    int HeadLocationX;
    int HeadLocationY;

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x, y) == 1) {
                HeadLocationX = x;
                HeadLocationY = y;
            }
        }
    }

    if (HeadLocationX == 0) {
        Alive = false;
        std::cout << "you lose in ";
        return;
    }

    if (GetSnakeMapData(HeadLocationX - 1, HeadLocationY) != 0) {
        Alive = false;
        std::cout << "you lose in ";
        return;
    }

    else if (GetAppleMapData(HeadLocationX - 1, HeadLocationY) == APPLE_DATA) {
        SetAppleMapData(HeadLocationX - 1, HeadLocationY, -1);
        for (int Iteration = 0; Iteration < 1; Iteration++) {
            AppleLocationX = (int) random() % this->MapSize;
            AppleLocationY = (int) random() % this->MapSize;
            if (GetSnakeMapData(AppleLocationX, AppleLocationY) > 0  || GetAppleMapData(AppleLocationX, AppleLocationY) == -1 || GetAppleMapData(AppleLocationX, AppleLocationY)) {
                Iteration--;
                SpawnTry = SpawnTry + 1;
            } else {
                SetAppleMapData(AppleLocationX,AppleLocationY,APPLE_DATA);
            }

            if (SpawnTry > MAX_SPAWN_TRY) {
                this->Alive = false;
                std::cout << "you win in ";
                return;
            }
        }
        SetAppleMapData(HeadLocationX - 1, HeadLocationY, 0);
        SnakeLength++;
    }

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x, y) != 0) {
                SetSnakeMapData(x , y, GetSnakeMapData(x, y) + 1);
            }
            if (GetSnakeMapData(x , y) > SnakeLength) {
                SetSnakeMapData(x , y, 0);
            }
        }
    }

    SetSnakeMapData(HeadLocationX - 1, HeadLocationY, 1);
}

void Map::NextFrameDown() {
    int SpawnTry;
    int AppleLocationX;
    int AppleLocationY;
    int HeadLocationX;
    int HeadLocationY;

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x, y) == 1) {
                HeadLocationX = x;
                HeadLocationY = y;
            }
        }
    }

    if (HeadLocationX == MapSize) {
        Alive = false;
        std::cout << "you lose in ";
        return;
    }

    if (GetSnakeMapData(HeadLocationX + 1, HeadLocationY) != 0) {
        Alive = false;
        std::cout << "you lose in ";
        return;
    }

    else if (GetAppleMapData(HeadLocationX + 1, HeadLocationY) == APPLE_DATA) {
        SetAppleMapData(HeadLocationX + 1, HeadLocationY, -1);
        SpawnTry = 0;
        for (int Iteration = 0; Iteration < 1; Iteration++) {
            AppleLocationX = (int) random() % this->MapSize;
            AppleLocationY = (int) random() % this->MapSize;
            if (GetSnakeMapData(AppleLocationX, AppleLocationY) > 0  || GetAppleMapData(AppleLocationX, AppleLocationY) == -1 || GetAppleMapData(AppleLocationX, AppleLocationY)) {
                Iteration--;
                SpawnTry = SpawnTry + 1;
            } else {
                SetAppleMapData(AppleLocationX,AppleLocationY,APPLE_DATA);
            }

            if (SpawnTry > MAX_SPAWN_TRY) {
                this->Alive = false;
                std::cout << "you win in ";
                return;
            }
        }
        SetAppleMapData(HeadLocationX + 1, HeadLocationY, 0);
        SnakeLength++;
    }

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x, y) != 0) {
                SetSnakeMapData(x , y, GetSnakeMapData(x, y) + 1);
            }
            if (GetSnakeMapData(x , y) > SnakeLength) {
                SetSnakeMapData(x , y, 0);
            }
        }
    }

    SetSnakeMapData(HeadLocationX + 1, HeadLocationY, 1);
}

void Map::NextFrameRight() {
    int SpawnTry;
    int AppleLocationX;
    int AppleLocationY;
    int HeadLocationX;
    int HeadLocationY;

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x, y) == 1) {
                HeadLocationX = x;
                HeadLocationY = y;
            }
        }
    }

    if (HeadLocationY == MapSize) {
        Alive = false;
        std::cout << "you lose in ";
        return;
    }

    if (GetSnakeMapData(HeadLocationX, HeadLocationY + 1) != 0) {
        Alive = false;
        std::cout << "you lose in ";
        return;
    }

    else if (GetAppleMapData(HeadLocationX, HeadLocationY + 1) == APPLE_DATA) {
        SetAppleMapData(HeadLocationX, HeadLocationY + 1, -1);
        SpawnTry = 0;
        for (int Iteration = 0; Iteration < 1; Iteration++) {
            AppleLocationX = (int) random() % this->MapSize;
            AppleLocationY = (int) random() % this->MapSize;
            if (GetSnakeMapData(AppleLocationX, AppleLocationY) > 0  || GetAppleMapData(AppleLocationX, AppleLocationY) == -1 || GetAppleMapData(AppleLocationX, AppleLocationY)) {
                Iteration--;
                SpawnTry = SpawnTry + 1;
            } else {
                SetAppleMapData(AppleLocationX,AppleLocationY,APPLE_DATA);
            }

            if (SpawnTry > MAX_SPAWN_TRY) {
                this->Alive = false;
                std::cout << "you win in ";
                return;
            }
        }
        SetAppleMapData(HeadLocationX, HeadLocationY + 1, 0);
        SnakeLength++;
    }

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x, y) != 0) {
                SetSnakeMapData(x , y, GetSnakeMapData(x, y) + 1);
            }
            if (GetSnakeMapData(x , y) > SnakeLength) {
                SetSnakeMapData(x , y, 0);
            }
        }
    }

    SetSnakeMapData(HeadLocationX, HeadLocationY + 1, 1);
}

void Map::NextFrameLeft() {
    int SpawnTry;
    int AppleLocationX;
    int AppleLocationY;
    int HeadLocationX;
    int HeadLocationY;

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x, y) == 1) {
                HeadLocationX = x;
                HeadLocationY = y;
            }
        }
    }

    if (HeadLocationY == 0) {
        Alive = false;
        std::cout << "you lose in ";
        return;
    }

    if (GetSnakeMapData(HeadLocationX, HeadLocationY - 1) != 0) {
        Alive = false;
        std::cout << "you lose in ";
        return;
    }

    else if (GetAppleMapData(HeadLocationX, HeadLocationY - 1) == APPLE_DATA) {
        SetAppleMapData(HeadLocationX, HeadLocationY - 1, -1);
        SpawnTry = 0;
        for (int Iteration = 0; Iteration < 1; Iteration++) {
            AppleLocationX = (int) random() % this->MapSize;
            AppleLocationY = (int) random() % this->MapSize;
            if (GetSnakeMapData(AppleLocationX, AppleLocationY) > 0  || GetAppleMapData(AppleLocationX, AppleLocationY) == -1 || GetAppleMapData(AppleLocationX, AppleLocationY)) {
                Iteration--;
                SpawnTry = SpawnTry + 1;
            } else {
                SetAppleMapData(AppleLocationX,AppleLocationY,APPLE_DATA);
            }

            if (SpawnTry > MAX_SPAWN_TRY) {
                this->Alive = false;
                std::cout << "you win in ";
                return;
            }
        }
        SetAppleMapData(HeadLocationX, HeadLocationY - 1, 0);
        SnakeLength++;
    }

    for (int x = 0; x < MapSize; x++) {
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x, y) != 0) {
                SetSnakeMapData(x , y, GetSnakeMapData(x, y) + 1);
            }
            if (GetSnakeMapData(x , y) > SnakeLength) {
                SetSnakeMapData(x , y, 0);
            }
        }
    }

    SetSnakeMapData(HeadLocationX, HeadLocationY - 1, 1);
}

void Map::DisplayMap() {
    for (int Iteration = 0; Iteration < MapSize + 1; Iteration++) {
        std::cout << "# ";
    }

    std::cout << "#" << std::endl;

    for (int x = 0; x < MapSize; x++) {
        std::cout << "#";
        for (int y = 0; y < MapSize; y++) {
            if (GetSnakeMapData(x ,y) == 0 && GetAppleMapData(x, y) == 0) {
                std::cout << "  ";
            } else if (GetSnakeMapData(x ,y) == 0 && GetAppleMapData(x, y) == 1) {
                std::cout << " @";
            } else if (GetSnakeMapData(x ,y) > 1 && GetAppleMapData(x, y) == 0) {
                std::cout << " □";
            } else if (GetSnakeMapData(x ,y) == 1 && GetAppleMapData(x, y) == 0) {
                std::cout << " ■";
            }
        }
        std::cout << " #" << std::endl;
    }

    for (int Iteration = 0; Iteration < MapSize + 1; Iteration++) {
        std::cout << "# ";
    }

    std::cout << "#" << std::endl;
}