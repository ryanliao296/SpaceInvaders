#include "mysteryship.hpp"

//mystery ship constructor that loads the image
MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
}

//destructor that frees memory by unloading the mystery ship texture
MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

//method to spawn the mystery ship by intitializing the position and selecting a random side to spawn
void MysteryShip::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0,1);

    if(side == 0)
    {
        position.x = 0;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }
    alive = true;
}

//update method by updating position and once it reaches the other side of the screen it is not alive anymore
void MysteryShip::Update()
{
    if(alive)
    {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width || position.x < 0)
        {
            alive = false;
        }
    }
}

//method to draw mysteryship
void MysteryShip::Draw()
{
    if(alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}