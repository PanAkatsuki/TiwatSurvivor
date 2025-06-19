#include <graphics.h>
#include <time.h>
#include <vector>

#include "Global.h"
#include "Pimon.h"
#include "Bullet.h"
#include "EnemyBoar.h"
#include "PlayerController.h"
#include "Atlas.h"
#include "Animation.h"
#include "TiwatSurvivorFunctionLibrary.h"
#include "StructType.h"
#include "Button.h"


#pragma comment(lib, "Winmm.lib")


bool bIsGameActivate = true;
bool bIsGameStarted = false;

int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	std::shared_ptr<IMAGE> MenuImage = std::make_shared<IMAGE>();
	loadimage(MenuImage.get(), _T("img/menu.png"));

	std::shared_ptr<FButtonImageSet> StartButtonImageSet = std::make_shared<FButtonImageSet>();
	loadimage(StartButtonImageSet->IdleImage.get(), _T("img/ui_start_idle.png"));
	loadimage(StartButtonImageSet->HoveredImage.get(), _T("img/ui_start_hovered.png"));
	loadimage(StartButtonImageSet->PushedImage.get(), _T("img/ui_start_pushed.png"));
	std::shared_ptr<UStartButton> StartButton = std::make_shared<UStartButton>(StartButtonImageSet);

	std::shared_ptr<FButtonImageSet> QuitButtonImageSet = std::make_shared<FButtonImageSet>();
	loadimage(QuitButtonImageSet->IdleImage.get(), _T("img/ui_quit_idle.png"));
	loadimage(QuitButtonImageSet->HoveredImage.get(), _T("img/ui_quit_hovered.png"));
	loadimage(QuitButtonImageSet->PushedImage.get(), _T("img/ui_quit_pushed.png"));
	std::shared_ptr<UQuitButton> QuitButton = std::make_shared<UQuitButton>(QuitButtonImageSet);

	ExMessage Message;

	IMAGE BackgroundImage;
	loadimage(&BackgroundImage, _T("img/background.png"));

	mciSendString(_T("open mus/bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open mus/hit.mp3 alias hit"), NULL, 0, NULL);

	FAtlasSet PimonAtlasSet;
	PimonAtlasSet.LeftAtlas = std::make_shared<UAtlas>(_T("img/player_left_%d.png"), 6);
	PimonAtlasSet.RightAtlas = std::make_shared<UAtlas>(_T("img/player_right_%d.png"), 6);
	PimonAtlasSet.ShadowAtlas = std::make_shared<UAtlas>(_T("img/shadow_player.png"), 1);

	FAtlasSet EnemyBoarAtlasSet;
	EnemyBoarAtlasSet.LeftAtlas = std::make_shared<UAtlas>(_T("img/enemy_left_%d.png"), 6);
	EnemyBoarAtlasSet.RightAtlas = std::make_shared<UAtlas>(_T("img/enemy_right_%d.png"), 6);
	EnemyBoarAtlasSet.ShadowAtlas = std::make_shared<UAtlas>(_T("img/shadow_enemy.png"), 1);

	std::shared_ptr<APimon> Pimon = std::make_shared<APimon>(PimonAtlasSet);

	std::vector<std::shared_ptr<AEnemy>> EnemyList;

	BeginBatchDraw();

	while (bIsGameActivate)
	{
		clock_t StartTime = clock();

		while (peekmessage(&Message))
		{
			if (bIsGameStarted)
			{
				Pimon->GetPlayerController()->ProcessEvent(Message);
			}
			else
			{
				StartButton->ProcessEvent(Message);
				QuitButton->ProcessEvent(Message);
			}
		}

		if (bIsGameStarted)
		{
			UTiwatSurvivorFunctionLibrary::TryGenerateEnemyBoar(EnemyList, EnemyBoarAtlasSet);

			Pimon->Update();

			for (const std::shared_ptr<AEnemy> Enemy : EnemyList)
			{
				if (!Enemy->GetTargetCharacter())
				{
					Enemy->SetTargetCharacter(Pimon);
				}

				for (const std::shared_ptr<UBullet>& Bullet : Pimon->GetBulletList())
				{
					Enemy->CheckBulletCollision(*Bullet);
				}

				Enemy->CheckPlayerCollision(Pimon);
				Enemy->Move();
			}

			for (size_t i = 0; i < EnemyList.size(); i++)
			{
				if (EnemyList[i]->bIsDead)
				{
					Pimon->SetScore(Pimon->GetScore() + 1);

					std::swap(EnemyList[i], EnemyList.back());
					EnemyList.pop_back();
				}
			}
		}
		else
		{

		}

		cleardevice();

		if (bIsGameStarted)
		{
			putimage(0, 0, &BackgroundImage);

			Pimon->RendAnimationAndBullet();

			for (const std::shared_ptr<AEnemy> Enemy : EnemyList)
			{
				Enemy->GetCurrentShadowAnimation()->Rend(Enemy->CalculateShadowPosition(), 5);
				Enemy->GetCurrentAnimation()->Rend(Enemy->GetPosition(), 5);
			}

			UTiwatSurvivorFunctionLibrary::DrawPlayScore(Pimon->GetScore());
		}
		else
		{
			putimage(0, 0, MenuImage.get());
			StartButton->Rend();
			QuitButton->Rend();
		}

		FlushBatchDraw();

		clock_t EndTime = clock();
		clock_t DeltaTime = EndTime - StartTime;
		if (DeltaTime < 1000 / 60)
		{
			Sleep(1000 / 60 - DeltaTime);
		}
	}

	EndBatchDraw();
}