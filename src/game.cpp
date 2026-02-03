#include "game.h"
#include <random>
Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    gameOverMenu = false;
    exitMenu = false;
    exitGame = false;
    navigation = 2;
    score = 0;
    continueGame = false;
    // InitAudioDevice();
    music = LoadMusicStream("Music/game-music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Music/rotate-sound.wav");
    clearSound = LoadSound("Music/clear-sound.wav");
    SetGameDifficulty(0.2);
}
Game::~Game()
{
    UnloadMusicStream(music);
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}
void Game::SetGameDifficulty(float level)
{
    gameDifficulty = level;
}
float Game::returnGameDifficulty()
{
    return gameDifficulty;
}
Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}
vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch ((nextBlock.id))
    {
    case 3:
        nextBlock.Draw(355, 290);
        break;
    case 4:
        nextBlock.Draw(355, 280);
        break;
    default:
        nextBlock.Draw(370, 270);
        break;
    }
}
void Game::GameOverHandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && (keyPressed == KEY_ESCAPE || keyPressed == KEY_Q))
    {
        gameOverMenu = true;
    }
    switch (keyPressed)
    {
    case KEY_ENTER:
        gameOver = false;
        gameOverMenu = true;
        // Reset();
        break;
    }
}
void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        GameOverHandleInput();
        // gameOver = true;
        // Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0, 1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}
void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}
void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}
void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.col))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleard = grid.ClearFullRows();
    if (rowsCleard > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleard, 0);
    }
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        if (grid.isCellEmpty(item.row, item.col) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    gameOver = false;
    gameOverMenu = false;
    exitMenu = false;
    exitGame = false;
    navigation = 2;
    score = 0;
    continueGame = false;
    SetGameDifficulty(0.2);
}

void Game::UpdateScore(int linesCleard, int moveDownPoints)
{
    switch (linesCleard)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }
    score += moveDownPoints;
}
