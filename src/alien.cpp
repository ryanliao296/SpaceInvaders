#include "alien.hpp"

//array to hold each image of the alien
Texture2D Alien::alienImages[3] = {};

//alien constructor that initializes type of alien, position and alien image
Alien::Alien(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;

    if(alienImages[type - 1].id == 0)
    {
        switch(type)
        {
            case 1: 
                alienImages[0] = LoadTexture("Graphics/alien_1.png");
                break;
            case 2:
                alienImages[1] = LoadTexture("Graphics/alien_2.png");
                break;
            case 3:
                alienImages[2] = LoadTexture("Graphics/alien_3.png");
                break;
            default:
                alienImages[0] = LoadTexture("Graphics/alien_1.png");
                break;
        }
    }
}

//method to draw the alien
void Alien::Draw()
{
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

//function that returns which type of alien an alien is 
int Alien::GetType()
{
    return type;
}

//method to free memory by unloading the alien textures
void Alien::UnloadImages()
{
    for(int i = 0; i < 4; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

//method to give a rectangle of the alien's position to check for collisions 
Rectangle Alien::GetRect()
{
    return {position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height)};
}

//moves the aliens left and right
void Alien::Update(int direction)
{
    position.x += direction;
}
