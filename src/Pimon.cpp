#include "Pimon.h"

// Constructor
Pimon::Pimon()
{
	// Animation
	AnimeShadow = new Animation(AtlasPimonShadow.get(), 45);
	AnimeLeft = new Animation(AtlasPimonLeft.get(), 45);
	AnimeRight = new Animation(AtlasPimonRight.get(), 45);

	// Default
	m_Direction = Direction::left;
	m_Pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	m_ShadowPos = { WINDOW_WIDTH / 2 + FRAME_LENGTH - SHADOW_LENGTH * 2,
		WINDOW_HEIGHT / 2 + FRAME_HEIGHT - SHADOW_HEIGHT / 2 };
	m_Speed = 5;
	isMoveUp = false;
	isMoveDown = false;
	isMoveLeft = false;
	isMoveRight = false;
	score = 0;
}
Pimon::~Pimon()
{
	delete AnimeShadow;
	delete AnimeLeft;
	delete AnimeRight;
}

// Default
Pimon::Direction Pimon::GetDirection() const
{
	return (m_Direction == Direction::left) ? Direction::left : Direction::right;
}
int Pimon::GetPosX() const
{
	return m_Pos.x;
}
int Pimon::GetPosY() const
{
	return m_Pos.y;
}
int Pimon::GetShadowPosX() const
{
	return m_ShadowPos.x;
}
int Pimon::GetShadowPosY() const
{
	return m_ShadowPos.y;
}
unsigned int Pimon::GetScore() const
{
	return score;
}

// Event
void Pimon::ProcessEvent(ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			isMoveUp = true;
			break;
		case VK_DOWN:
			isMoveDown = true;
			break;
		case VK_LEFT:
			isMoveLeft = true;
			if (m_Direction == Direction::right)
			{
				m_Direction = Direction::left;
			}
			break;
		case VK_RIGHT:
			isMoveRight = true;
			if (m_Direction == Direction::left)
			{
				m_Direction = Direction::right;
			}
			break;
		default:
			break;
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			isMoveUp = false;
			break;
		case VK_DOWN:
			isMoveDown = false;
			break;
		case VK_LEFT:
			isMoveLeft = false;
			break;
		case VK_RIGHT:
			isMoveRight = false;
			break;
		default:
			break;
		}
	}
}
void Pimon::Move()
{
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
	if (m_Pos.x < 0)
	{
		m_Pos.x = 0;
	}
	if (m_Pos.y < 0)
	{
		m_Pos.y = 0;
	}
	if (m_Pos.x > 1280 - FRAME_LENGTH)
	{
		m_Pos.x = 1280 - FRAME_LENGTH;
	}
	if (m_Pos.y > 720 - FRAME_HEIGHT - SHADOW_HEIGHT)
	{
		m_Pos.y = 720 - FRAME_HEIGHT - SHADOW_HEIGHT;
	}
	m_ShadowPos.x = m_Pos.x + FRAME_LENGTH - SHADOW_LENGTH * 2;
	m_ShadowPos.y = m_Pos.y + FRAME_HEIGHT - SHADOW_HEIGHT / 2;
}
void Pimon::ScorePlus()
{
	score++;
}

// Rend
void Pimon::Rend()
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
void Pimon::DrawScore()
{
	static TCHAR text[64];
	_stprintf_s(text, _T("Score: %d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	outtextxy(WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100, text);
}