#include "game.hpp"
#include <iostream>
#include <fstream>
using namespace std;

//Constructor that initializes the game by creating obstacles, aliens, initializing the movement of the aliens + alien laser cooldown and mysteryship + spawn rate and amount of lives
//and game should be running
//load sounds too
Game::Game()
{
    music = LoadMusicStream("Sounds/music.ogg");
    explosion = LoadSound("Sounds/explosion.ogg");
    InitGame();
    PlayMusicStream(music);
}

//Destructor that unloads the images of the aliens and sounds once the game is done
Game::~Game()
{
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosion);
}

//Update game state
void Game::Update()
{

    if(run)
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

        //check for collisions between objects
        CheckForCollisions();
    }
    else
    {
        //reset the game
        if(IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
    }
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
    if(run)
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
        obstacles.push_back(Obstacle({offset, float(GetScreenHeight() - 200)}));
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
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            MoveAliensDown(4);
        }
        if(alien.position.x < 25)
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

//method to check if there are collsions between objects or lasers and properly deletes them from the screen and update score/high score
void Game::CheckForCollisions()
{
    //spaceship lasers
    for(auto& laser: spaceship.lasers)
    {
        auto it = aliens.begin();
        while(it != aliens.end())
        {
            if(CheckCollisionRecs(it -> GetRect(), laser.GetRect()))
            {
                PlaySound(explosion);
                if(it -> type == 1)
                {
                    score += 100;
                }
                else if(it -> type == 2)
                {
                    score += 200;
                }
                else if(it -> type == 3)
                {
                    score += 300;
                }

                CheckHighScore();
                it = aliens.erase(it);
                laser.active = false;
            }
            else
            {
                it++;
            }
        }

        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it -> GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    it++;
                }
            }
        }

        if(CheckCollisionRecs(mysteryShip.GetRect(), laser.GetRect()))
        {
            PlaySound(explosion);
            mysteryShip.alive = false;
            laser.active = false;
            score += 500;
            CheckHighScore();
        }
    }

    //alien lasers
    for(auto& laser: alienLasers)
    {
        if(CheckCollisionRecs(laser.GetRect(), spaceship.GetRect()))
        {
            laser.active = false;
            lives--;
            if(lives == 0)
            {
                GameOver();
            }
        }

        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it -> GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    it++;
                }
            }
        }
    }

    //alien collision with obstacle
    for(auto& alien: aliens)
    {
        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it -> GetRect(), alien.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

        if(CheckCollisionRecs(alien.GetRect(), spaceship.GetRect()))
        {
           GameOver();
        }
    }
}

//method to set the run variable to false, the game should not be running if game over
void Game::GameOver()
{
    run = false;
}

//initializes all the variables and objects
void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienShot = 0;
    timeLastSpawn = 0;
    mysteryShipSpawnCooldown = GetRandomValue(10,20);
    lives = 3;
    run = true;
    score = 0;
    highScore = LoadHighScore();
}

//check if current score is higher than old high score and update if necessary
void Game::CheckHighScore()
{
    if(score > highScore)
    {
        highScore = score;
        SaveHighScore(highScore);
    }
}

//save high score in a text file 
void Game::SaveHighScore(int highScore)
{
    ofstream highScoreFile("highscore.txt");
    if(highScoreFile.is_open())
    {
        highScoreFile << highScore;
        highScoreFile.close();
    }
    else
    {
        cerr << "Failed to save highscore" << endl;
    }
}

//load high score form text file
int Game::LoadHighScore()
{
    int loadedHighScore = 0;
    ifstream highScoreFile("highscore.txt");
    if(highScoreFile.is_open())
    {
        highScoreFile >> loadedHighScore;
        highScoreFile.close();
    }
    else
    {
        cerr << "Failed to load highscore" << endl;
    }

    return loadedHighScore;
}

//reset all the objects 
void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}
