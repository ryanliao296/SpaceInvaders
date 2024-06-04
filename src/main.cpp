#include <raylib.h>
#include "game.hpp"
#include "obstacle.hpp"

int main()
{
    Color gray = {29, 29, 27, 255};
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth, windowHeight, "C++ Space Invaders");
    SetTargetFPS(60);

    Game game;
    

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(gray);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}