#include <raylib.h>
#include "game.hpp"
#include <string>


string FormatWithLeadingZeros(int num, int width)
{
    string scoreText = to_string(num);
    int leadingZeros = 5 - scoreText.length();
    return scoreText = string(leadingZeros, '0') + scoreText;
}

int main()
{
    Color gray = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "C++ Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipimage = LoadTexture("Graphics/spaceship.png");
    SetTargetFPS(60);

    Game game;


    while(WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
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

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        DrawTextEx(font, "HIGH SCORE", {570, 15}, 34, 2, yellow);
        string highScoreText = FormatWithLeadingZeros(game.highScore, 5);
        DrawTextEx(font, highScoreText.c_str(), {655, 40}, 34, 2, yellow);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}