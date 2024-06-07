#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

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

        vector<Alien> aliens;
        vector<Alien> CreateAliens();
        void MoveAliens();
        int aliensDirection;
        void MoveAliensDown(int distance);
        vector<Laser> alienLasers;
        void AlienShoot();
        constexpr static float alienLaserCooldown = .35;
        float timeLastAlienShot;

        MysteryShip mysteryShip;
        float mysteryShipSpawnCooldown;
        float timeLastSpawn;

};