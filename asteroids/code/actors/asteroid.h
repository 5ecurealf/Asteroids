#pragma once

#include "space_object.h"

class Asteroid : public SpaceObject //inherit from SpaceObject
{
public:
    Asteroid(const SpaceObject &position); //COPY CONSTRUCTOR

    bool IsHits(const SpaceObject &);
    void Draw(Drawer &drawer);
    //void Update();

private:
    const int m_size = 250;
    const int m_hitSize = 50;
   // int m_speed;
};
