#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

Color background = {173,204,96,255};
Color darkg = {43,51,24,255};

int cellSize=30;
int cellCount=25; 
int offset = 75;

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
        bool addSegment = false;
        void Draw()
        {
            for(unsigned int i = 0; i < body.size();i++)
            {
                float x=body[i].x;
                float y=body[i].y;
                Rectangle segment = Rectangle{offset+ x*cellSize,offset+ y*cellSize, (float)cellSize, (float)cellSize};
                DrawRectangleRounded(segment,0.5,6,darkg);

            }

        }
        void Update()
        {   
            body.push_front(Vector2Add(body[0],direction));
            
            if(addSegment == true)
            {
                
                addSegment = false;
            }
            else{
                body.pop_back();
            
        }
    }
        void Reset()
        {
            body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
            direction ={1,0};
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

int main() 
{
    
    InitWindow(2*offset + cellSize*cellCount,2*offset+cellSize*cellCount, "Retro Snake");
    SetTargetFPS(60);

    Game game = Game();

    //game loop
    while(WindowShouldClose() == false)
    {
        //1. Event
        BeginDrawing();
        
        if (eventTriggered(0.1))
        {
            game.Update();
        }
        
        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = {0,-1};
            game.running=true;
        }
        if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = {0,1};
            game.running=true;
        }
        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1,0};
            game.running=true;
        }
        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x !=-1)
        {
            game.snake.direction = {1,0};
            game.running=true;
        }


        //2. Updating postn
        
        //3. Draw
        ClearBackground(background);
        DrawRectangleLinesEx(Rectangle{(float)offset-5,(float)offset-5,(float)cellSize*cellCount+10,(float)cellSize*cellCount+10},5,darkg);
        DrawText("Retro Snake",offset-5,20,40,darkg);
        DrawText(TextFormat("Score: %i",game.score),offset-5,offset+cellSize*cellCount+10,40,darkg);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}