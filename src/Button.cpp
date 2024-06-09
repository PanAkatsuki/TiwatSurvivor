#include "Button.h"

Button::Button(RECT rect, LPCTSTR pathIdleIMG, LPCTSTR pathHoveredIMG, LPCTSTR pathPushedIMG)
{
	m_Region = rect;
	loadimage(&m_IdleIMG, pathIdleIMG);
	loadimage(&m_HoveredIMG, pathHoveredIMG);
	loadimage(&m_PushedIMG, pathPushedIMG);
	status = Status::Idle;
}
Button::~Button()
{

}

bool Button::CheckCursorHit(int x, int y)
{
	return x >= m_Region.left && x <= m_Region.right &&
		y >= m_Region.top && y <= m_Region.bottom;
}

void Button::ProcessEvent(const ExMessage& msg)
{
	switch (msg.message)
	{
	case WM_MOUSEMOVE:
		if (status == Status::Idle && CheckCursorHit(msg.x, msg.y))
		{
			status = Status::Hovered;
		}
		else if (status == Status::Hovered && !CheckCursorHit(msg.x, msg.y))
		{
			status = Status::Idle;
		}
		break;
	case WM_LBUTTONDOWN:
		if (status == Status::Hovered)
		{
			status = Status::Pushed;
		}
		break;
	case WM_LBUTTONUP:
		if (status == Status::Pushed)
		{
			OnClick();
		}
		break;
	}
}

void Button::Rend()
{
	switch (status)
	{
	case Status::Idle:
		putimage(m_Region.left, m_Region.top, &m_IdleIMG);
		break;
	case Status::Hovered:
		putimage(m_Region.left, m_Region.top, &m_HoveredIMG);
		break;
	case Status::Pushed:
		putimage(m_Region.left, m_Region.top, &m_PushedIMG);
		break;
	}
}

StartButton::StartButton(RECT rect, LPCTSTR pathIdleIMG, LPCTSTR pathHoveredIMG, LPCTSTR pathPushedIMG)
	: Button(rect, pathIdleIMG, pathHoveredIMG, pathPushedIMG)
{

}
StartButton::~StartButton()
{

}

QuitButton::QuitButton(RECT rect, LPCTSTR pathIdleIMG, LPCTSTR pathHoveredIMG, LPCTSTR pathPushedIMG)
	: Button(rect, pathIdleIMG, pathHoveredIMG, pathPushedIMG)
{

}
QuitButton::~QuitButton()
{
	
}