#include "Bullet.h"

Bullet::Bullet(Pimon& pimon)
{
	m_Pos = { pimon.GetPosX(), pimon.GetPosY() };
}
Bullet::~Bullet()
{

}

int Bullet::GetPosX() const
{
	return m_Pos.x;
}
int Bullet::GetPosY() const
{
	return m_Pos.y;
}
void Bullet::ChangePosX(int x)
{
	m_Pos.x = x;
}
void Bullet::ChangePosY(int y)
{
	m_Pos.y = y;
}

void Bullet::Rend()
{
	setlinecolor(RGB(255, 155, 50));
	setfillcolor(RGB(200, 75, 10));
	fillcircle(m_Pos.x, m_Pos.y, RADIUS);
}