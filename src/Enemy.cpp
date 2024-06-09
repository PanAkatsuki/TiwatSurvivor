#include "Enemy.h"


Enemy::Enemy()
{
	// Animation
	AnimeShadow = new Animation(AtlasEnemyShadow.get(), 45);
	AnimeLeft = new Animation(AtlasEnemyLeft.get(), 45);
	AnimeRight = new Animation(AtlasEnemyRight.get(), 45);

	// Default
	m_Pos = { 0, 0 };
	SpawnEdge edge = (SpawnEdge)(rand() % 4);
	switch (edge)
	{
	case SpawnEdge::up:
		m_Pos.x = rand() % WINDOW_WIDTH;
		m_Pos.y = 0 - FRAME_HEIGHT;
		break;
	case SpawnEdge::down:
		m_Pos.x = rand() % WINDOW_WIDTH;
		m_Pos.y = WINDOW_HEIGHT;
		break;
	case SpawnEdge::left:
		m_Pos.x = -FRAME_LENGTH;
		m_Pos.y = rand() % WINDOW_HEIGHT;
		break;
	case SpawnEdge::right:
		m_Pos.x = WINDOW_WIDTH;
		m_Pos.y = rand() % WINDOW_HEIGHT;
		break;
	default:
		break;
	}

	m_Direction = Direction::left;
	m_ShadowPos = { 0 + FRAME_LENGTH - SHADOW_LENGTH * 2,
		0 + FRAME_HEIGHT - SHADOW_HEIGHT / 2 };
	m_Speed = 2;
	m_Alive = true;
}
Enemy::~Enemy()
{
	delete AnimeShadow;
	delete AnimeLeft;
	delete AnimeRight;
}

bool Enemy::CheckBulletCollision(Bullet& bullet) const
{
	bool isOverlapX = bullet.GetPosX() >= m_Pos.x && bullet.GetPosX() <= m_Pos.x + FRAME_LENGTH;
	bool isOverlapY = bullet.GetPosY() >= m_Pos.y && bullet.GetPosY() <= m_Pos.y + FRAME_HEIGHT;
	return isOverlapX && isOverlapY;
}

bool Enemy::CheckPimonCollision(Pimon& pimon) const
{
	POINT checkPos = { m_Pos.x + FRAME_LENGTH / 2, m_Pos.y + FRAME_HEIGHT / 2 };
	bool isOverlapX = checkPos.x >= pimon.GetPosX() && checkPos.x <= pimon.GetPosX() + pimon.FRAME_LENGTH;
	bool isOverlapY = checkPos.y >= pimon.GetPosY() && checkPos.y <= pimon.GetPosY() + pimon.FRAME_HEIGHT;
	return isOverlapX && isOverlapY;
}
void Enemy::CheckHurt(Bullet& bullet)
{
	if (CheckBulletCollision(bullet))
	{
		m_Alive = false;
	}
}
bool Enemy::CheckAlive() const
{
	return m_Alive;
}

void Enemy::Move(Pimon& pimon)
{
	bool isMoveUp = false;
	bool isMoveDown = false;
	bool isMoveLeft = false;
	bool isMoveRight = false;
	if (m_Pos.x > pimon.GetPosX())
	{
		isMoveLeft = true;
		isMoveRight = false;
		m_Direction = Direction::left;
	}
	else if (m_Pos.x == pimon.GetPosX())
	{
		isMoveLeft = false;
		isMoveRight = false;
	}
	else if (m_Pos.x < pimon.GetPosX())
	{
		isMoveLeft = false;
		isMoveRight = true;
		m_Direction = Direction::right;
	}
	if (m_Pos.y > pimon.GetPosY())
	{
		isMoveUp = true;
		isMoveDown = false;
	}
	else if (m_Pos.y == pimon.GetPosY())
	{
		isMoveUp = false;
		isMoveDown = false;
	}
	else if (m_Pos.y < pimon.GetPosY())
	{
		isMoveUp = false;
		isMoveDown = true;
	}
	int dirX = isMoveRight - isMoveLeft;
	int dirY = isMoveDown - isMoveUp;
	double dir = sqrt(dirX * dirX + dirY * dirY);
	if (dir != 0)
	{
		double normalizedX = 0;
		double normalizedY = 0;
		if (dir > 1)
		{
			normalizedX = dirX / 1.4;
			normalizedY = dirY / 1.4;
		}
		else
		{
			normalizedX = dirX;
			normalizedY = dirY;
		}
		m_Pos.x += (int)(normalizedX * m_Speed);
		m_Pos.y += (int)(normalizedY * m_Speed);
	}
	m_ShadowPos.x = m_Pos.x + FRAME_LENGTH - SHADOW_LENGTH * 2;
	m_ShadowPos.y = m_Pos.y + FRAME_HEIGHT - SHADOW_HEIGHT;
}

void Enemy::Rend()
{
	AnimeShadow->Rend(m_ShadowPos.x, m_ShadowPos.y, 10);
	if (m_Direction == Direction::left)
	{
		AnimeLeft->Rend(m_Pos.x, m_Pos.y, 10);
	}
	else if (m_Direction == Direction::right)
	{
		AnimeRight->Rend(m_Pos.x, m_Pos.y, 10);
	}
}