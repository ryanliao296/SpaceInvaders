#include "game.hpp"
#include <iostream>
using namespace std;

Game::Game()
{

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
    cout << "Vector size: " << spaceship.lasers.size() << endl;
}

//Draws each object of the game (spaceships and lasers)
void Game::Draw()
{
    spaceship.Draw();

    for(auto& laser: spaceship.lasers)
    {
        laser.Draw();
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
            ++it;
    }
}