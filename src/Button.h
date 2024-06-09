#pragma once
#pragma comment(lib, "Winmm.lib")

#include <graphics.h>

#include "Global.h"

class Button
{
protected:
	virtual void OnClick() = 0;
private:
	enum Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};
private:
	RECT m_Region;
	IMAGE m_IdleIMG;
	IMAGE m_HoveredIMG;
	IMAGE m_PushedIMG;
	Status status;
private:
	bool CheckCursorHit(int x, int y);
public:
	// Constructor
	Button(RECT rect, LPCTSTR pathIdleIMG, LPCTSTR pathHoveredIMG, LPCTSTR pathPushedIMG);
	~Button();

	// EventProcess
	void ProcessEvent(const ExMessage& msg);

	// Rend
	void Rend();
};

class StartButton : public Button
{
protected:
	void OnClick()
	{
		isGameStart = true;
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	}
public:
	StartButton(RECT rect, LPCTSTR pathIdleIMG, LPCTSTR pathHoveredIMG, LPCTSTR pathPushedIMG);
	~StartButton();


};

class QuitButton : public Button
{
protected:
	void OnClick()
	{
		running = false;
	}
public:
	QuitButton(RECT rect, LPCTSTR pathIdleIMG, LPCTSTR pathHoveredIMG, LPCTSTR pathPushedIMG);
	~QuitButton();
};