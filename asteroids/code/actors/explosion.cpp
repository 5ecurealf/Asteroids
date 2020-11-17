#include <sstream>
#include <iomanip>

#include "explosion.h"

Explosion::Explosion(const SpaceObject &position) : SpaceObject(position) {}

Action Explosion::Update(float elapsedTime)
{
    if (m_stage < 15)
    {
        ++m_stage;
    }
    return Action::NONE;
}

void Explosion::Draw(Drawer &drawer)
{
    std::stringstream fileName;
    fileName << "explosion_" << std::setw(3) << std::setfill('0') << m_stage << ".png";

    drawer.DrawImage(fileName.str().c_str(), m_x - 31, m_y - 31);
}
