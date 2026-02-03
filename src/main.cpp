#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"
#include "game.h"
#include "colors.h"
#include "button.hpp"
#include <iostream>
using namespace std;

double lastUpdateTime = 0;
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
enum class GameState
{
    MAIN_MENU,
    DIFFICULTY_MENU,
    GAME,
    GAME_OVER,
    EXIT
};

int main()
{
    const int screenWidth = 750;
    const int screenHeight = 780;
    InitWindow(screenWidth, screenHeight, "Tetris by Ognjen");
    InitAudioDevice();
    SetTargetFPS(60);
    Font font = LoadFontEx("Font/CabalBold.ttf", 64, 0, 0);
    Texture2D background = LoadTexture("Picture/Tetris-Logo.jpg");
    Texture2D backgroundMenu = LoadTexture("Picture/meni-background.jpg");
    Texture2D backgroundOver = LoadTexture("Picture/game-overbeckground.png");

    Button startButton{"Picture/Start.png", {(float)(screenWidth / 2 - 150), 200}, 0.65};
    Button exitButton{"Picture/exit1.png", {(float)(screenWidth / 2 - 150), 500}, 0.65};
    Button easyButton{"Picture/easy-difficulty.png", {(float)(screenWidth / 2 - 125), 200}, 1.2};
    Button mediumButton{"Picture/medium-difficuly.png", {(float)(screenWidth / 2 - 125), 300}, 1.2};
    Button hardButton{"Picture/hard-difficulty.png", {(float)(screenWidth / 2 - 125), 400}, 1.2};
    GameState gameState = GameState::MAIN_MENU;
    Game game;
    while (!WindowShouldClose() && gameState != GameState::EXIT)
    {
        UpdateMusicStream(game.music);
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        BeginDrawing();
        ClearBackground(BLUE);
        if (gameState == GameState::MAIN_MENU)
        {
            DrawTexture(background, 0, 0, WHITE);
            const char *welcomeText = "WELCOME TO TETRIS BY OGI!";
            Vector2 welcomeSize = MeasureTextEx(font, welcomeText, 46, 4);
            DrawTextEx(font, welcomeText, {(float)(screenWidth / 2 - welcomeSize.x / 2), 50}, 46, 4, WHITE);
            startButton.DrawButton();
            exitButton.DrawButton();
            if (startButton.isPressed(mousePosition, mousePressed))
                gameState = GameState::DIFFICULTY_MENU;
            if (exitButton.isPressed(mousePosition, mousePressed))
                gameState = GameState::EXIT;
        }
        else if (gameState == GameState::DIFFICULTY_MENU)
        {
            DrawTexture(backgroundMenu, 0, 0, WHITE);
            DrawRectangleRounded({(float)(screenWidth / 2 - 275), 490, 550, 60}, 0.3, 6, lightBlue);
            DrawRectangleRounded({(float)(screenWidth / 2 - 300), 560, 600, 60}, 0.3, 6, lightBlue);
            DrawRectangleRounded({(float)(screenWidth / 2 - 275), 625, 550, 60}, 0.3, 6, lightBlue);
            const char *difficultyText = "Choose a difficulty!";
            Vector2 difficultySize = MeasureTextEx(font, difficultyText, 50, 2);
            DrawTextEx(font, difficultyText, {(float)(screenWidth / 2 - difficultySize.x / 2), 50}, 50, 2, WHITE);
            const char *easyText = "EASY: BABY SPEED!";
            Vector2 easySize = MeasureTextEx(font, easyText, 50, 2);
            DrawTextEx(font, easyText, {(float)(screenWidth / 2 - easySize.x / 2), 495}, 50, 2, green);
            const char *mediumText = "MEDIUM: NORMAL SPEED!";
            Vector2 mediumSize = MeasureTextEx(font, mediumText, 50, 2);
            DrawTextEx(font, mediumText, {(float)(screenWidth / 2 - mediumSize.x / 2), 565}, 50, 2, yellow);
            const char *hardText = "HARD: WARP SPEED!";
            Vector2 hardSize = MeasureTextEx(font, hardText, 50, 2);
            DrawTextEx(font, hardText, {(float)(screenWidth / 2 - hardSize.x / 2), 630}, 50, 2, red);
            easyButton.DrawButton();
            mediumButton.DrawButton();
            hardButton.DrawButton();
            if (easyButton.isPressed(mousePosition, mousePressed))
            {
                game.Reset();
                game.SetGameDifficulty(0.35);
                gameState = GameState::GAME;
            }
            if (mediumButton.isPressed(mousePosition, mousePressed))
            {
                game.Reset();
                game.SetGameDifficulty(0.2);
                gameState = GameState::GAME;
            }
            if (hardButton.isPressed(mousePosition, mousePressed))
            {
                game.Reset();
                game.SetGameDifficulty(0.08);
                gameState = GameState::GAME;
            }
        }
        else if (gameState == GameState::GAME)
        {
            game.HandleInput();
            if (EventTriggered(game.returnGameDifficulty()))
            {
                game.MoveBlockDown();
            }
            ClearBackground(blue);
            const char *scoreLabel = "Score";
            Vector2 scoreLabelSize = MeasureTextEx(font, scoreLabel, 38, 2);
            DrawTextEx(font, scoreLabel, {420 + (170 - scoreLabelSize.x) / 2, 15}, 38, 2, WHITE);
            const char *nextLabel = "Next";
            Vector2 nextLabelSize = MeasureTextEx(font, nextLabel, 38, 2);
            DrawTextEx(font, nextLabel, {420 + (170 - nextLabelSize.x) / 2, 175}, 38, 2, WHITE);
            const char *messLabel = "Message";
            Vector2 messLabelSize = MeasureTextEx(font, messLabel, 38, 2);
            DrawTextEx(font, messLabel, {420 + (170 - messLabelSize.x) / 2, 475}, 38, 2, WHITE);
            DrawRectangleRounded({390, 525, 270, 80}, 0.3, 6, lightBlue);
            if (game.score <= 200)
            {
                Vector2 textSize = MeasureTextEx(font, "Do better!", 38, 2);
                DrawTextEx(font, "Do better!", {440 + (170 - textSize.x) / 2, 545}, 38, 2, RED);
            }
            else if (game.score > 200 && game.score < 600)
            {
                Vector2 textSize = MeasureTextEx(font, "Not bad!", 38, 2);
                DrawTextEx(font, "Not bad!", {440 + (170 - textSize.x) / 2, 545}, 38, 2, YELLOW);
            }
            else
            {
                Vector2 textSize = MeasureTextEx(font, "Great!", 38, 2);
                DrawTextEx(font, "Great!", {440 + (170 - textSize.x) / 2, 545}, 38, 2, GREEN);
            }
            DrawRectangleRounded({420, 55, 170, 60}, 0.3, 6, lightBlue);
            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
            DrawTextEx(font, scoreText, {420 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
            DrawRectangleRounded({420, 215, 170, 180}, 0.3, 6, lightBlue);
            game.Draw();
            if (game.gameOver)
            {
                gameState = GameState::GAME_OVER;
            }
        }
        else if (gameState == GameState::GAME_OVER)
        {
            ClearBackground(RED);
            DrawTexture(backgroundOver, 0, 0, WHITE);
            const char *gameOverText = "Game Over!";
            Vector2 gameOverSize = MeasureTextEx(font, gameOverText, 64, 2);
            DrawTextEx(font, gameOverText, {(float)(screenWidth / 2 - gameOverSize.x / 2), 100}, 64, 2, BLACK);
            const char *yourScoreText = "Your score:";
            Vector2 yourScoreSize = MeasureTextEx(font, yourScoreText, 44, 2);
            DrawTextEx(font, yourScoreText, {(float)(screenWidth / 2 - yourScoreSize.x / 2), 220}, 44, 2, BLACK);
            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 scoreSize = MeasureTextEx(font, scoreText, 74, 5);
            DrawTextEx(font, scoreText, {(float)(screenWidth / 2 - scoreSize.x / 2), 300}, 74, 5, BLUE);
            const char *enterText = "Press ENTER to Main Menu!";
            Vector2 enterSize = MeasureTextEx(font, enterText, 42, 2);
            DrawTextEx(font, enterText, {(float)(screenWidth / 2 - enterSize.x / 2), 400}, 42, 2, RED);
            const char *escText = "ESC or Q TO exit!";
            Vector2 escSize = MeasureTextEx(font, escText, 42, 2);
            DrawTextEx(font, escText, {(float)(screenWidth / 2 - escSize.x / 2), 500}, 42, 2, BLACK);
            int keyPressed = GetKeyPressed();
            if (keyPressed == KEY_ENTER)
            {
                game.Reset();
                gameState = GameState::MAIN_MENU;
            }
            if (keyPressed == KEY_ESCAPE || keyPressed == KEY_Q)
            {
                gameState = GameState::EXIT;
            }
        }
        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(backgroundMenu);
    UnloadTexture(backgroundOver);
    UnloadFont(font);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}