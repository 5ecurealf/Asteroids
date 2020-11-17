#include <SDL.h>

#include "space_ship.h"

SpaceShip::SpaceShip(const SpaceObject &startPoint, const int speed, const float fireSpeed)
    : SpaceObject{startPoint}, m_speed{speed}, m_fireSpeed{fireSpeed}
{
}

bool SpaceShip::IsHits(const SpaceObject &point)    
{
    return point.m_x >= m_x - m_hitSize &&
           point.m_x <= m_x + m_hitSize &&
           point.m_y >= m_y - m_hitSize &&
           point.m_y <= m_y + m_hitSize;
}


//this code waits for the an event e.g hit arrows to move the spaceship around 
//spaceship returns an action SHOT/NONE so that we know when to send a shot and from what posiion 

Action SpaceShip::Update(float elapsedTime)     
{
    Action result = Action::NONE;                   
    m_timeSinceLastShot += elapsedTime;
    const Uint8 *keystate = SDL_GetKeyboardState(nullptr);
    if (keystate[SDL_SCANCODE_LEFT])
    {
        m_x -= m_speed;
    }
    if (keystate[SDL_SCANCODE_RIGHT])
    {
        m_x += m_speed;
    }
    if (keystate[SDL_SCANCODE_UP])
    {
        m_y -= m_speed;
    }
    if (keystate[SDL_SCANCODE_DOWN])
    {
        m_y += m_speed;
    }

    if (keystate[SDL_SCANCODE_SPACE])
    {
        if (m_timeSinceLastShot >= m_fireSpeed)
        {
            result = Action::SHOT;
            m_timeSinceLastShot = 0;
        }
    }

    return result;
}

void SpaceShip::Draw(Drawer &drawer)
{
    drawer.DrawImage("ship.png", m_x - 20, m_y - 20);
}