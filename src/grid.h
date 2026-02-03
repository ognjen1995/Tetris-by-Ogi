#pragma once
#include <vector>
#include <raylib.h>
using namespace std;
class Grid
{
public:
    Grid();
    int grid[25][10];
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOutside(int, int);
    bool isCellEmpty(int, int);
    int ClearFullRows();

private:
    int numRows;
    int numCols;
    int cellSize;
    vector<Color> colors;
    bool IsRowFull(int);
    void ClearRow(int);
    void MoveRowDown(int, int);
};