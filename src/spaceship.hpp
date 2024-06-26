#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>
using namespace std;

class Spaceship
{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void ShootLaser();
        vector<Laser> lasers;
        Rectangle GetRect();
        void Reset();

    private:
        Texture2D image;
        Vector2 position;
        double lastShotTime;
        Sound laser;
};