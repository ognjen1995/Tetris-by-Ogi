#include "grid.h"
#include <iostream>
#include "colors.h"
using namespace std;

Grid::Grid()
{
    numRows = 25;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}
void Grid::Initialize()
{
    for (int red = 0; red < numRows; red++)
    {
        for (int kol = 0; kol < numCols; kol++)
        {
            grid[red][kol] = 0;
        }
    }
}
void Grid::Print()
{
    for (int red = 0; red < numRows; red++)
    {
        for (int kol = 0; kol < numCols; kol++)
        {
            cout << grid[red][kol] << " ";
        }
        cout << endl;
    }
}

void Grid::Draw()
{
    for (int red = 0; red < numRows; red++)
    {
        for (int kol = 0; kol < numCols; kol++)
        {
            int cellValue = grid[red][kol];
            DrawRectangle(kol * cellSize + 11, red * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int red, int kol)
{
    if (red >= 0 && red < numRows && kol >= 0 && kol < numCols)
    {
        return false;
    }
    return true;
}

bool Grid::isCellEmpty(int red, int kol)
{
    if (grid[red][kol] == 0)
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int complited = 0;
    for (int red = numRows - 1; red >= 0; red--)
    {
        if (IsRowFull(red))
        {
            ClearRow(red);
            complited++;
        }
        else if (complited > 0)
        {
            MoveRowDown(red, complited);
        }
    }
    return complited;
}

bool Grid::IsRowFull(int red)
{
    for (int col = 0; col < numCols; col++)
    {
        if (grid[red][col] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int red)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[red][col] = 0;
    }
}

void Grid::MoveRowDown(int red, int numRows)
{
    for (int kol = 0; kol < numCols; kol++)
    {
        grid[red + numRows][kol] = grid[red][kol];
        grid[red][kol] = 0;
    }
}
