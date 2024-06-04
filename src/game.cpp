#include "game.hpp"
#include <iostream>
using namespace std;

//Constructor that initializes the game by creating obstacles
Game::Game()
{
    obstacles = CreateObstacles();
}

Game::~Game()
{

}

//Update game state
void Game::Update()
{
    //update all the laser positions and states
    for(auto& laser: spaceship.lasers)
    {
        laser.Update();
    }

    //delete any inactive lasers
    DeleteInactiveLasers();
}

//Draws each object of the game (spaceships,lasers and obstacles)
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
