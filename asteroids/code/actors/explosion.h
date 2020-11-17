#pragma once

#include "space_object.h"
//They Explosion class is the same as the spaceship, however with less inputs 
//so just will need to input a startpoint and then we make it disappear
class Explosion : public SpaceObject
{
public:
    explicit Explosion(const SpaceObject &position);

    Action Update(float elapsedTime);
    void Draw(Drawer &drawer);

private:
    int m_stage = 0;
};
