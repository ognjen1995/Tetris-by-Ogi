#pragma once;
#include "button.hpp"

Button::Button(const char *imagePath, Vector2 imagePosition, float scale)
{
    Image image = LoadImage(imagePath);
    int orgiginalWidth = image.width;
    int originalHeight = image.height;
    int newWidth = static_cast<int>(orgiginalWidth * scale);
    int newHeight = static_cast<int>(originalHeight * scale);
    ImageResize(&image, newWidth, newHeight);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = imagePosition;
}
Button::~Button()
{
    UnloadTexture(texture);
}
void Button::DrawButton()
{
    DrawTextureV(texture, position, WHITE);
}

bool Button::isPressed(Vector2 mosuePos, bool mousePressed)
{
    Rectangle rect = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    if (CheckCollisionPointRec(mosuePos, rect) && mousePressed)
    {
        return true;
    }
    return false;
}
