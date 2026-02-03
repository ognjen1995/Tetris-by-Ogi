
#include "block.h"
using namespace std;
Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}
void Block::Draw(int offsetX, int offsetY)
{
    vector<Position> tiles = GetCellPosition();
    for (Position item : tiles)
    {
        DrawRectangle(item.col * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
void Block::Move(int red, int kol)
{
    rowOffset += red;
    columnOffset += kol;
}
vector<Position> Block::GetCellPosition()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> pomjeranjeTiles;
    for (Position item : tiles)
    {
        Position novaPozicija = Position(item.row + rowOffset, item.col + columnOffset);
        pomjeranjeTiles.push_back(novaPozicija);
    }
    return pomjeranjeTiles;
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}
