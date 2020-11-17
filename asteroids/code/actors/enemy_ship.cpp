#include <SDL.h>

#include "enemy_ship.h"

EnemyShip::EnemyShip(const SpaceObject &startPoint)
    : SpaceObject{startPoint}
{
}

bool EnemyShip::IsHits(const SpaceObject &point)    //increases the size of the hit area of the ship 
{                                                   //wnere m_hitSize is delcared in the enemy_ship.h file as
    return point.m_x >= m_x - m_hitSize &&          //20 this is because the image is 20x20
           point.m_x <= m_x + m_hitSize &&
           point.m_y >= m_y - m_hitSize &&
           point.m_y <= m_y + m_hitSize;
}

void EnemyShip::ChangeDirection()
{
    m_direction = !m_direction;
}

Action EnemyShip::Update(float elapsedTime)     
{
    Action result = Action::NONE;       
    m_x += m_direction ? 2 : -2;            //keep moving from left part of the screen to the right 

    m_timeSinceLastShot += elapsedTime;
    if (m_timeSinceLastShot >= m_fireSpeed)
    {
        result = Action::SHOT;
        m_timeSinceLastShot = 0;
    }

    return result;
}

void EnemyShip::Draw(Drawer &drawer)
{
    drawer.DrawImage("ship_enemy.png", m_x - 20, m_y - 20, 180.0f, 20, 20); //the 180.0f flips the image upside down
}