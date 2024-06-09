#include <graphics.h>

#include <iostream>
#include <memory>

#include "Global.h"
#include "Pimon.h"
#include "Animation.h"
#include "Enemy.h"
#include "Button.h"

void TryGenerateEnemy(std::vector<Enemy*>& enemyList)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
	{
		enemyList.push_back(new Enemy());
		counter = 0;
	}
}

void UpdateBulletsPos(std::vector<Bullet*>& bulletList, Pimon& pimon)
{
	clock_t startClock = clock();
	const double RADIAL_SPEED = 0.0040;
	const double TRANGENT_SPEED = 0.0040;
	double radianInterval = 2 * 3.14159 / bulletList.size();
	POINT pimonPos = { pimon.GetPosX(), pimon.GetPosY() };
	double radius = 100 + 25 * sin(startClock * RADIAL_SPEED);
	for (size_t i = 0; i < bulletList.size(); i++)
	{
		double radian = startClock * TRANGENT_SPEED + radianInterval * i;
		bulletList[i]->ChangePosX(pimonPos.x + pimon.FRAME_LENGTH / 2 + (int)(radius * cos(radian)));
		bulletList[i]->ChangePosY(pimonPos.y + pimon.FRAME_HEIGHT / 2 + (int)(radius * sin(radian)));
	}
}
void DrawBullet(std::vector<Bullet*>& bulletList)
{
	for (Bullet* bullet : bulletList)
	{
		bullet->Rend();
	}
}

int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, NULL);

	if(running == false)
	{
		running = true;
	}

	ExMessage msg;
	IMAGE img_menu;
	IMAGE img_background;
	mciSendString(_T("open mus/bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open mus/hit.mp3 alias hit"), NULL, 0, NULL);
	Pimon pimon;
	std::vector<Enemy*> enemyList;
	std::vector<Bullet*> bulletList;

	RECT regionStartButton, regionQuitButton;
	regionStartButton.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	regionStartButton.right = regionStartButton.left + BUTTON_WIDTH;
	regionStartButton.top = 430;
	regionStartButton.bottom = regionStartButton.top + BUTTON_HEIGHT;

	regionQuitButton.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	regionQuitButton.right = regionQuitButton.left + BUTTON_WIDTH;
	regionQuitButton.top = 550;
	regionQuitButton.bottom = regionQuitButton.top + BUTTON_HEIGHT;

	StartButton startButton = StartButton(regionStartButton, _T("img/ui_start_idle.png"), _T("img/ui_start_hovered.png"), _T("img/ui_start_pushed.png"));
	QuitButton quitButton = QuitButton(regionQuitButton, _T("img/ui_quit_idle.png"), _T("img/ui_quit_hovered.png"), _T("img/ui_quit_pushed.png"));

	Bullet bullet1(pimon);
	bulletList.push_back(&bullet1);
	Bullet bullet2(pimon);
	bulletList.push_back(&bullet2);
	Bullet bullet3(pimon);
	bulletList.push_back(&bullet3);

	loadimage(&img_menu, _T("img/menu.png"), 0, 0, false);
	loadimage(&img_background, _T("img/background.png"), 0, 0, false);

	BeginBatchDraw();

	while (running)
	{
		clock_t startTime = clock();

		// Event Process
		while (peekmessage(&msg, -1, true))
		{
			if (isGameStart)
			{
				pimon.ProcessEvent(msg);
			}
			else
			{
				startButton.ProcessEvent(msg);
				quitButton.ProcessEvent(msg);
			}
		}

		// Draw
		cleardevice();
		if(isGameStart)
		{
			putimage(0, 0, &img_background, SRCCOPY);
			pimon.Rend();
			pimon.DrawScore();
			for (Enemy* enemy : enemyList)
			{
				enemy->Rend();
			}
			DrawBullet(bulletList);
		}
		else
		{
			putimage(0, 0, &img_menu, SRCCOPY);
			startButton.Rend();
			quitButton.Rend();
		}

		if(isGameStart)
		{
			// Move
			pimon.Move();
			TryGenerateEnemy(enemyList);
			for (Enemy* enemy : enemyList)
			{
				enemy->Move(pimon);
			}
			UpdateBulletsPos(bulletList, pimon);

			// Check Collision
			for (Enemy* enemy : enemyList)
			{
				if (enemy->CheckPimonCollision(pimon))
				{
					TCHAR text[128];
					_stprintf_s(text, _T("Score: %d"), pimon.GetScore());
					MessageBox(GetHWnd(), text, _T("Game is over"), MB_OK);
					running = false;
					break;
				}
			}

			// Check Dead
			for (size_t i = 0; i < enemyList.size(); i++)
			{
				for (Bullet* bullet : bulletList)
				{
					enemyList[i]->CheckHurt(*bullet);
					if (!enemyList[i]->CheckAlive())
					{
						std::swap(enemyList[i], enemyList.back());
						Enemy* tmp = enemyList.back();
						enemyList.pop_back();
						delete tmp;
						pimon.ScorePlus();
						mciSendString(_T("play hit from 0"), NULL, 0, NULL);
						break;
					}
				}
			}
		}

		FlushBatchDraw();

		clock_t endTime = clock();
		clock_t deltaTime = endTime - startTime;
		if (deltaTime < 1000 / 60)
		{
			Sleep(1000 / 60 - deltaTime);
		}
	}

	EndBatchDraw();
}