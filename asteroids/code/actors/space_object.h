#pragma once

#include "action.h"
#include "../drawer.h"

//the position m_x and m_y allows us to be able to copy the positions of the objects to one another 
//for example, to fire a shot from the ship we can just copy the position of the ship to the position of the shot 
//so SpaceObject will be declared in all objects 

struct SpaceObject
{
    int m_x;  

    int m_y;

    bool IsHits(const SpaceObject &) { return false; };

    Action Update(float elapsedTime) { return Action::NONE; }; //any space object after updating either returns shot or nothing, Asteroid = none
                                                               // Spaceship = NONE or SHOT 
    void Draw(Drawer &drawer){};
};
