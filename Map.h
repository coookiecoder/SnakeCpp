class Map {
public:
    Map(int Size, int AppleNumber);
    void NextFrameUp();
    void NextFrameDown();
    void NextFrameRight();
    void NextFrameLeft();
    void DisplayMap();
    bool GetAlive();
private:
    bool Alive;
    int MapSize;
    int SnakeLength;
    int * AppleMap;
    int * SnakeMap;
    int GetAppleMapData(int x, int y);
    int GetSnakeMapData(int x, int y);
    void SetAppleMapData(int x, int y, int value);
    void SetSnakeMapData(int x, int y, int value);
};