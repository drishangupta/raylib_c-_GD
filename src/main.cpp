#include <raylib.h>

Color background = {173,204,96,255};
Color snake = {43,51,24,255};

int cellSize=30;
int cellCount=25; 

class Food
{
public:
    Vector2 position;
    Texture2D texture;
    Food()
    {
        Image image = LoadImage("Graphics/chuha.png");
        Image *ptr = &image;
        ImageResize(ptr,cellSize,cellSize);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();

    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture,position.x*cellSize,position.y*cellSize,WHITE);
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0,cellCount-1);
        float y = GetRandomValue(0,cellCount-1);
        return Vector2{x,y};
    }

};

int main() 
{
    int ballX=400;
    int ballY=400;
    
    InitWindow(cellSize*cellCount,cellSize*cellCount, "Retro Snake");
    SetTargetFPS(60);

    Food food = Food();
    //game loop
    while(WindowShouldClose() == false)
    {
        //1. Event 
        
        //2. Updating postn
        
        //3. Draw
        BeginDrawing();
        ClearBackground(background);
        food.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}