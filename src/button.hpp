#pragma once;
#include <raylib.h>

class Button
{
private:
    Texture2D texture;
    Vector2 position;

public:
    Button(const char *imagePath, Vector2 imagePosition, float scale);
    ~Button();
    void DrawButton();
    bool isPressed(Vector2 mosuePos, bool mousePressed);
};
