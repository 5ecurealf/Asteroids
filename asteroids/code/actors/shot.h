#pragma once

#include "space_object.h"
//shot class made from the same class as the asteroid, we just will pass the postion at which to 
//fire from and the Direction of shot


//Enum Syntax

//// Declaration
//enum class EnumName { Value1, Value2, ... ValueN };
//
//// Initialisation
//EnumName ObjectName = EnumName::Value;

class Shot : public SpaceObject
{
public:
    enum class Direction   // used enum to create a up and down indicator 
    {
        UP,
        DOWN,
    };

    Shot(const SpaceObject &startPoint, const Direction direction);

    Action Update(float elapsedTime);

    void Draw(Drawer &drawer);

    Direction GetDirection() const;

private:
    Direction m_direction;
};