#include "laser.hpp"
#include <iostream>
using namespace std;

//Laser constructor that initializes position, speed and states the laser is active
Laser::Laser(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    active = true;
}

//Draws the laser on the screen if it is active
void Laser::Draw()
{
    if(active)
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

//Updates the position of the laser vertically
void Laser::Update()
{
    position.y += speed;

    //If laser is active and moved off screen set to inactive
    if(active)
    {
        if(position.y > GetScreenHeight() || position.y < 0)
        {
            active = false;
            cout << "Laser Inactive" << endl;
        }
    }
}