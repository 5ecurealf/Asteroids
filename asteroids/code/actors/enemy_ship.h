#pragma once

#include "space_object.h"
//They EnemyShip class is the same as the spaceship, however with less inputs to contructor as itll move from left to right 
//so just will need to input a startpoint 
class EnemyShip : public SpaceObject
{
public:
    explicit EnemyShip(const SpaceObject &startPoint); //works without being explicit shoudl I keep, 

    bool IsHits(const SpaceObject &);
    void ChangeDirection();
    Action Update(float elapsedTime);
    void Draw(Drawer &drawer);

private:
    bool m_direction = true;        //determines if the enemy needs to turn around 
    float m_timeSinceLastShot = 0;  // to make the shots a set rate 
    const float m_fireSpeed = 0.5;  // to make the shots a set rate 
    const int m_hitSize = 20;
};
