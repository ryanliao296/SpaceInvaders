#include <raylib.h>
#include "game.hpp"


int main()
{
    Color gray = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "C++ Space Invaders");

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipimage = LoadTexture("Graphics/spaceship.png");
    SetTargetFPS(60);

    Game game;


    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(gray);
        DrawRectangleRoundedLines({10, 10, 780, 780}, .18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        if(game.run)
        {
            DrawTextEx(font, "LEVEL 1", {570, 740}, 34, 2, yellow);
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        float x = 50.0;
        for(int i = 0; i < game.lives; i++)
        {
            DrawTextureV(spaceshipimage, {x, 745}, WHITE);
            x += 50;
        }
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}