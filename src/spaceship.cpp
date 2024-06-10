#include "spaceship.hpp"

//Spaceship constructor that loads image, sets position and initialize shot cooldown timer
Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight()- image.height - 100;
    lastShotTime = 0;
}

//Spaceship destructor unloads image
Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

//Draws the spaceship on screen at a certain position
void Spaceship::Draw()
{
    DrawTextureV(image, position, WHITE);
}

//Updates the spaceship's movement left and ensures it stays on screen
void Spaceship::MoveLeft()
{
    position.x -= 7;

    if(position.x < 25)
    {
        position.x = 25;
    }
}

//Updates the spaceship's movement right and ensures it stays on screen
void Spaceship::MoveRight()
{
    position.x += 7;

    if(position.x > GetScreenWidth() - image.width - 25)
    {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

//Method to shoot laser from ship
void Spaceship::ShootLaser()
{
    //Ensures a cooldown for shots and adds new lasers to list
    if(GetTime() - lastShotTime >= .35)
    {
        lasers.push_back(Laser({position.x + image.width/2 - 2,position.y},-6));
        lastShotTime = GetTime();
    }
}

//method to return a rectangle of the spaceship's position to check for collisions
Rectangle Spaceship::GetRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

//reset the lasers and position of the spaceship
void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}
