#pragma once
#include "functions.h"
#include "snake.h"
#include "food.h"

class Game{
    public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    void Draw()
    {
        food.Draw();
        snake.Draw();
    }
    void Update()
    {   
        if(running)
        {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
    }

    void CheckCollisionWithFood()
    {
        if(Vector2Equals(snake.body[0],food.position))
        {
            food.position=food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score++;
        }
    }
    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
    }
    void CheckCollisionWithEdges()
    {
       // Wrap horizontally
        if (snake.body[0].x >= cellCount)
            snake.body[0].x = 0;
        else if (snake.body[0].x < 0)
            snake.body[0].x = cellCount - 1;

        // Wrap vertically
        if (snake.body[0].y >= cellCount)
            snake.body[0].y = 0;
        else if (snake.body[0].y < 0)
            snake.body[0].y = cellCount - 1;
    }
    void CheckCollisionWithTail()
    {
        std::deque<Vector2> headlessbody = snake.body;
        headlessbody.pop_front();
        if(ElementInDeque(snake.body[0],headlessbody))
        {
            GameOver();
        }
    }
    
};
