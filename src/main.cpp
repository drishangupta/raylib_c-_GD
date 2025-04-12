#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

Color background = {173,204,96,255};
Color snake = {43,51,24,255};

int cellSize=30;
int cellCount=25; 

double lastUpdateTime=0;
bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i=0;i<deque.size();i++)
    {
        if (Vector2Equals(deque[i],element))
        {
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval)
{
    double currentTime= GetTime();
    if (currentTime - lastUpdateTime >=interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{

    public:
        std::deque<Vector2> body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};

        Vector2 direction ={1,0};
        void Draw()
        {
            for(unsigned int i = 0; i < body.size();i++)
            {
                float x=body[i].x;
                float y=body[i].y;
                Rectangle segment = Rectangle{x*cellSize, y*cellSize, (float)cellSize, (float)cellSize};
                DrawRectangleRounded(segment,0.5,6,snake);

            }

        }
        void Update()
        {
            body.pop_back();
            body.push_front(Vector2Add(body[0], direction));
        }

};

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
        DrawTexture(texture,position.x*cellSize,position.y*cellSize,WHITE);
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

class Game{
    public:
    Snake snake = Snake();
    Food food = Food(snake.body);

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }
    void Update()
    {
        snake.Update();
        CheckCollisionWithFood();
    }

    void CheckCollisionWithFood()
    {
        if(Vector2Equals(snake.body[0],food.position))
        {
            food.position=food.GenerateRandomPos(snake.body);
        }
    }
};

int main() 
{
    
    InitWindow(cellSize*cellCount,cellSize*cellCount, "Retro Snake");
    SetTargetFPS(60);

    Game game = Game();

    //game loop
    while(WindowShouldClose() == false)
    {
        //1. Event
        BeginDrawing();
        
        if (eventTriggered(0.4))
        {
            game.Update();
        }
        
        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = {0,-1};
        }
        if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = {0,1};
        }
        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1,0};
        }
        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x !=-1)
        {
            game.snake.direction = {1,0};
        }


        //2. Updating postn
        
        //3. Draw
        ClearBackground(background);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}