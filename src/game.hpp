#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"

class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();

    private:
        Spaceship spaceship;
        void DeleteInactiveLasers();
        vector<Obstacle> obstacles;
        vector<Obstacle> CreateObstacles();
};