#pragma once
#include "functions.h"

class Food
{
public:
    Vector2 position;
    Texture2D texture;
    Food(std::deque<Vector2> snakeBody)
    {
        Image image = LoadImage("Graphics/chuha.png");
        Image *ptr = &image;
        ImageResize(ptr,cellSize,cellSize);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);

    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture,offset + position.x*cellSize,offset+ position.y*cellSize,WHITE);
    }

    Vector2 GenerateRandomCellForFood()
    {
        float x = GetRandomValue(0,cellCount-1);
        float y = GetRandomValue(0,cellCount-1);
        return {x,y};
    }
    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody)
    {
        
        Vector2 position = GenerateRandomCellForFood();
        while (ElementInDeque(position, snakeBody))
        {
        GenerateRandomCellForFood();
        }
        return position;
    }

};