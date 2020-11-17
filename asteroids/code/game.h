
#pragma once

#include <list>

#include "actors/asteroid.h"
#include "actors/enemy_ship.h"
#include "actors/explosion.h"
#include "actors/shot.h"
#include "actors/space_ship.h"

class Drawer;

class Game
{
public:
    Game(Drawer &drawer, int width, int height);

    void Update(float elapsedTime);
    void Draw();

private:
    bool m_running = true;              //end game condition 
    int m_width;
    int m_height;
    int m_score = 0;
    Drawer &m_drawer;                   //declared drawer object
    SpaceShip m_spaceShip;              //declared spaceship object    

    std::list<Shot> m_shots;            //declared Shot Asteroid EnemyShip ... list objects as there will be multiple 
    std::list<Asteroid> m_asteroids;
    std::list<EnemyShip> m_enemies;
    std::list<Explosion> m_explosions;

};