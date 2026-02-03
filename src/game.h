#pragma once
#include "grid.h"
#include "blocks.cpp"
using namespace std;

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void GameOverHandleInput();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;
    Music music;
    void SetGameDifficulty(float level);

    float returnGameDifficulty();
    bool gameOverMenu;
    bool exitMenu;
    bool exitGame;
    bool continueGame;
    void Reset();
    int navigation;

private:
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    Grid grid;
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    // void Reset();
    void UpdateScore(int linesCleard, int moveDownPoints);
    Sound rotateSound;
    Sound nextSound;
    Sound clearSound;
    float gameDifficulty;
};