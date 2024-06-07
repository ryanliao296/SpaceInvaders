#include "game.hpp"
#include <iostream>
using namespace std;

//Constructor that initializes the game by creating obstacles, aliens, initializing the movement of the aliens + alien laser cooldown and mysteryship + spawn rate
Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienShot = 0;
    timeLastSpawn = 0;
    mysteryShipSpawnCooldown = GetRandomValue(10,20);
}

//Destructor that unloads the images of the aliens once the game is done
Game::~Game()
{
    Alien::UnloadImages();
}

//Update game state
void Game::Update()
{

    //update when the mysteryship should spawn and give a new random cooldown
    double currentTime = GetTime();
    if(currentTime - timeLastSpawn > mysteryShipSpawnCooldown)
    {
        mysteryShip.Spawn();
        timeLastSpawn = GetTime();
        mysteryShipSpawnCooldown = GetRandomValue(10,20);
    }

    //update all the laser positions and states
    for(auto& laser: spaceship.lasers)
    {
        laser.Update();
    }

    //move aliens
    MoveAliens();

    //choose random alien to shoot laser
    AlienShoot();
    for(auto& laser: alienLasers)
    {
        laser.Update();
    }

    //delete any inactive lasers
    DeleteInactiveLasers();

    //update the mystery ship
    mysteryShip.Update();
}

//Draws each object of the game (spaceships, lasers, obstacles, aliens and their lasers and mysteryship)
void Game::Draw()
{
    spaceship.Draw();

    for(auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }

    for(auto& obstacle: obstacles)
    {
        obstacle.Draw();
    }

    for(auto& alien: aliens)
    {
        alien.Draw();
    }

    for(auto& laser: alienLasers)
    {
        laser.Draw();
    }

    mysteryShip.Draw();
}

//takes a user input and move the ship or shoot a laser
void Game::HandleInput()
{
    if(IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    }
    else if(IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    }
    else if(IsKeyDown(KEY_SPACE))
    {
        spaceship.ShootLaser();
    }
}

//delete inactive lasers by checking if active and removing from vector
void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if(!it -> active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
            it++;
    }

    for(auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if(!it -> active)
        {
            it = alienLasers.erase(it);
        }
        else
            it++;
    }
}

//Method to create obstacles used in game constructor
vector<Obstacle> Game::CreateObstacles()
{
    //get width of obstacles and space in between each one
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float space = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    //create the four obstacles
    for(int i = 0; i < 4; i++)
    {
        float offset = (i + 1) * space + i * obstacleWidth;
        obstacles.push_back(Obstacle({offset, float(GetScreenHeight() - 100)}));
    }

    return obstacles;
}

//method to initialize the aliens
vector<Alien> Game::CreateAliens()
{
    vector<Alien> aliens;
    for(int row = 0; row < 5; row++)
    {
        for(int col = 0; col < 11; col++)
        {
            int alienType;
            if(row == 0)
            {
                alienType = 3;
            }
            else if(row == 1 || row == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }

            float x = 75 + col * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x,y}));

        }
    }

    return aliens;
}

//moves the aliens left and right in the bounds of the screen
void Game::MoveAliens()
{
    for(auto& alien: aliens)
    {
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth())
        {
            aliensDirection = -1;
            MoveAliensDown(4);
        }
        if(alien.position.x < 0)
        {
            aliensDirection = 1;
            MoveAliensDown(4);
        }
        alien.Update(aliensDirection);
    }
}

//moves the aliens down a row
void Game::MoveAliensDown(int distance)
{
    for(auto& alien: aliens)
    {
        alien.position.y += distance;
    }
}

//method for the aliens to shoot lasers and at a reasonable cooldown
void Game::AlienShoot()
{
    double currentTime = GetTime();
    if(currentTime - timeLastAlienShot >= alienLaserCooldown && !aliens.empty())
    {
        int rand = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[rand];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width/2, alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienShot = GetTime();
    }
}
