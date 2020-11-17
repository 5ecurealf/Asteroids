
#include "game.h"

#include <SDL.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <list>

#include "drawer.h"
                                                            //constexpr performance improvement computations at compile time rather than run time
                                                            //all values used to initial space objects within the game class below 
constexpr SpaceObject asteroidStartPoint = {200, 160};      //declares where the asteroid will start 
constexpr SpaceObject spaceShipStartPoint = {200, 300};     //declares where the spaceship will start 
constexpr int spaceShipSpeed = 5;                           //declares the speed of the spaceship
constexpr float spaceShipFireSpeed = 0.3f;                  //declares how fast the spaceship fires 

Game::Game(Drawer &drawer, int width, int height)
    : m_drawer{drawer},
      m_width{width},
      m_height{height},
      m_spaceShip{spaceShipStartPoint, spaceShipSpeed, spaceShipFireSpeed} 
{
    m_asteroids.emplace_back(asteroidStartPoint);
    m_enemies.emplace_back(EnemyShip({0, 40}));
}

void Game::Update(float elapsedTime)
{
    // the end of the game
    if (!m_running)
        return;

    if (m_spaceShip.Update(elapsedTime) == Action::SHOT)     //updates the spaceships and fires a shot if the keyboard event has taken place
    {                                                        //as the function Update() will return ACTION::SHOT
        m_shots.emplace_back(m_spaceShip, Shot::Direction::UP);  //create a shot in the position m_spaceShip in the upwards direction 
    }

    //m_asteroids.Update()

    for (auto &enemy : m_enemies) //go through all the enemies in the enimies list
    {
        if (enemy.Update(elapsedTime) == Action::SHOT) //if the enemy has fired a shot (enemy.Update(elapsedTime) returns SHOT) 
        {                                              ////create another shot at location enemy
            m_shots.emplace_back(enemy, Shot::Direction::DOWN); //emplace_back creates another item in the list ???
        }

        if (enemy.m_x < 0 || enemy.m_x > m_width || enemy.m_y < 0 && enemy.m_y > m_height) //if enemy reaches end of the window change direction 
        {
            enemy.ChangeDirection();
        }
    }

    for (auto it = m_shots.begin(); it != m_shots.end();)                            //removing the shots off screen
    {                                                                                // if the shot's position is beyond that of the screen remove shot
        if (it->m_x > 0 && it->m_x < m_width && it->m_y > 0 && it->m_y < m_height)   
        {
            it->Update(elapsedTime);
            ++it;
        }
        else
        {
            it = m_shots.erase(it);
        }
    }
    //for loop below   m_shots list of shots class which take inputs startpoint and direction so for loop goes through all the shots
    //and then we go through all the asteroids/enemies/our ship, using it->IsHits(shot) function we can see if we've hit the astroid 
    //if so we create an explosion and remove the asteroid 

    for (const auto &shot : m_shots) 
    {                               
        for (std::list<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end();) // go through all the asteroids 
        {
            if (it->IsHits(shot))  //if the position of the shot is the same as hit area of asteroid 
            {
                m_explosions.emplace_back(shot);  //create explosion and erase the asteroid
                it = m_asteroids.erase(it);       //get rid of the asteroid
            }
            else
            {
                ++it;
            }
        }

        if (shot.GetDirection() == Shot::Direction::UP)        // IF SHOT IS GOING UP AND HITS ENEMY CREATE EXPLOSION AND THEN 2 ENEMIES 
        {
            for (std::list<EnemyShip>::iterator it = m_enemies.begin(); it != m_enemies.end();)
            {
                if (it->IsHits(shot))
                {
                    m_explosions.emplace_back(shot);
                    m_enemies.emplace_back(EnemyShip({60, 40}));
                    m_enemies.emplace_back(EnemyShip({0, 40}));

                    it = m_enemies.erase(it);
                    ++m_score;
                }
                else
                {
                    ++it;
                }
            }
        }
        else if (m_spaceShip.IsHits(shot))
        {
            // handle end of the game
            m_running = false;                  
            m_explosions.emplace_back(shot);
        }
    }

    for (auto &explosion : m_explosions)
    {
        explosion.Update(elapsedTime);
    }
}

void Game::Draw()
{
    m_drawer.DrawImage("bg.png", 0, 0);
    m_spaceShip.Draw(m_drawer);
    for (auto &asteroid : m_asteroids) // LOOP THROUGH ALL THE ASTEROIDS (m_asteroids is a list) MADE AND DRAW THEM 
    {                                  //(auto &asteroid : m_asteroids) we don't know how many there will be made 
        asteroid.Draw(m_drawer);
    }
    for (auto &enemy : m_enemies)
    {
        enemy.Draw(m_drawer);
    }
    for (auto &shot : m_shots)
    {
        shot.Draw(m_drawer);
    }
    for (auto &explosion : m_explosions)
    {
        explosion.Draw(m_drawer);
    }

    std::stringstream scoreLabel;
    scoreLabel << "Score: " << std::setw(3) << std::setfill('0') << m_score; //creates a score text on the window, incrementing m_score 

    m_drawer.DrawText("arial.ttf", scoreLabel.str().c_str(), 40, 20, 50);

    if (!m_running)
    {
        m_drawer.DrawText("arial.ttf", "Game over!", 80, m_width / 2 - 200, m_height / 2);
    }
}