
#include "asteroid.h"


Asteroid::Asteroid(const SpaceObject &position) : SpaceObject{position} {}  //custom 

bool Asteroid::IsHits(const SpaceObject &point)         // increases the hit area of the asteroid 
{
    return point.m_x >= m_x - m_hitSize &&
           point.m_x <= m_x + m_hitSize &&
           point.m_y >= m_y - m_hitSize &&
           point.m_y <= m_y + m_hitSize;
}

//void Asteroid::Update(float elapsedTime)
//{
//    m_x += 10;
//}
   

void Asteroid::Draw(Drawer &drawer)
{
    drawer.DrawImage("asteroid.png", m_x - m_size / 2, m_y - m_size / 2);
}
