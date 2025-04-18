#include "functions.h"
#include "game.h"
#include "snake.h"
#include "food.h"

int main() 
{
    
    InitWindow(2*offset + cellSize*cellCount,2*offset+cellSize*cellCount, "Retro Snake");
    
    
    Game game = Game();

    //game loop
    while(WindowShouldClose() == false)
    {
        //1. Event
        BeginDrawing();
        
        if (IsKeyPressed(KEY_W) && gameSpeed>=0.02)
        {
            gameSpeed -= 0.02;
        }
        if (IsKeyPressed(KEY_S) && gameSpeed<=0.6)
        {
            gameSpeed += 0.02;
        }

        if (eventTriggered(gameSpeed))
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
        DrawText("Press W to Increase Speed",offset+465,20,20,darkg);
        DrawText("Press S to Decrease Speed",offset+460,40,20,darkg);

        DrawText(TextFormat("Score: %i",game.score),offset-5,offset+cellSize*cellCount+10,40,darkg);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}