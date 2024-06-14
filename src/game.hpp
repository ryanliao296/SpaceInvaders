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
        bool run;
        int lives;
        int score;
        int highScore;
        Music music;

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

        void CheckForCollisions();
        void GameOver();
        void Reset();
        void InitGame();
        void CheckHighScore();
        void SaveHighScore(int highScore);
        int LoadHighScore();

        Sound explosion;

};