#include <raylib.h>
Color background = {173,204,96,255};
Color snake = {43,51,24,255};
int main() 
{
    int ballX=400;
    int ballY=400;
    
    InitWindow(750,750, "Retro Snake");
    SetTargetFPS(60);
    //game loop
    while(WindowShouldClose() == false)
    {
        //1. Event 
        if(IsKeyDown(KEY_RIGHT))
        {
            ballX +=3;
        } else if (IsKeyDown(KEY_LEFT))
        {
            ballX -=3;
        } else if (IsKeyDown(KEY_DOWN))
        {
            ballY +=3;
        } else if (IsKeyDown(KEY_UP))
        {
            ballY -=3;
        }
        
        //2. Updating postn
        
        //3. Draw
        BeginDrawing();
        ClearBackground(background);
        DrawCircle(ballX,ballY,20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}