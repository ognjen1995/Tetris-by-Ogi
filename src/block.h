#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
using namespace std;

class Block
{
public:
    Block();
    int id;
    map<int, vector<Position>> cells;
    void Draw(int offsetX, int offsetY);
    void Move(int red, int kol);
    vector<Position> GetCellPosition();
    void Rotate();
    void UndoRotation();

private:
    int cellSize;
    int rotationState;
    vector<Color> colors;
    int rowOffset;
    int columnOffset;
};