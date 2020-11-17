
#include "shot.h"

//class for the shot SpaceObject 
//need to specify the direction of the shot, UP/DOWN and from where to fire SpaceObject

Shot::Shot(const SpaceObject &position, const Direction direction) : SpaceObject(position), m_direction{direction} {}

//don't return a shot from this SpaceObject, we look at the direction and if the direction is up we minus the speed and vice versa 
Action Shot::Update(float elapsedTime)
{
    switch (m_direction)
    {
    case Direction::UP:
        m_y -= 15;
        break;
    case Direction::DOWN:
        m_y += 15;
        break;

    default:
        break;
    }

    return Action::NONE;
}


//case statemment that handles if the show is coming downwards then invert the image otherwise stay the same 
void Shot::Draw(Drawer &drawer)
{
    switch (m_direction)
    {
    case Direction::UP:
        drawer.DrawImage("shot.png", m_x - 14, m_y - 16);
        break;
    case Direction::DOWN:
        drawer.DrawImage("shot.png", m_x - 14, m_y - 16, 180.0, 14, 16);
        break;

    default:
        break;
    }
}

Shot::Direction Shot::GetDirection() const
{
    return m_direction;
}
