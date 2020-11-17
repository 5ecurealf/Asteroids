#pragma once

#include "space_object.h"
//class to attributes and methods of the spaceship
//SpaceObject declared here as public so that the position variables m_y/m_x of SpaceObject can be accessed from here 
class SpaceShip : public SpaceObject
{
public:
    SpaceShip(const SpaceObject &startPoint, const int speed, const float fireSpeed);

    bool IsHits(const SpaceObject &);
    Action Update(float elapsedTime);
    void Draw(Drawer &drawer);

private:
    int m_speed;
    float m_fireSpeed;
    float m_timeSinceLastShot = 0;
    const int m_hitSize = 20;
};