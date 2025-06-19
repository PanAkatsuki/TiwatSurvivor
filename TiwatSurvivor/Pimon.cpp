#include "Pimon.h"

#include "Animation.h"
#include "Atlas.h"
#include "PlayerController.h"
#include "Bullet.h"



APimon::APimon(const FAtlasSet& InAtlasSet)
	: ACharacter(InAtlasSet)
{
	Speed = 3;
	Position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

	Controller = CreatePlayerController();

	BulletList.push_back(std::make_shared<UBullet>());

	for (const std::shared_ptr<UBullet>& Bullet : BulletList)
	{
		Bullet->SetOwner(this);
	}
}

APimon::~APimon()
{
}

std::shared_ptr<APlayerController> APimon::CreatePlayerController()
{
	std::shared_ptr<APlayerController> NewController = std::make_shared<APlayerController>();
	NewController->SetOwner(this);

	return NewController;
}

void APimon::Update()
{
	Move();
	UpdateBullet();

	/*static int Timer = 0;
	Timer++;
	if (Timer >= 100)
	{
		std::shared_ptr<UBullet> Bullet = std::make_shared<UBullet>();
		Bullet->SetOwner(this);
		BulletList.push_back(Bullet);

		Timer = 0;
	}*/
}

void APimon::Move()
{
	int DirectionX = Controller->GetbIsMoveRight() - Controller->GetbIsMoveLeft();
	int DirectionY = Controller->GetbIsMoveDown() - Controller->GetbIsMoveUp();

	if (DirectionX > 0)
	{
		CurrentAnimation = RightAnimation;
	}
	else if (DirectionX < 0)
	{
		CurrentAnimation = LeftAnimation;
	}

	double Length = sqrt(DirectionX * DirectionX + DirectionY * DirectionY);

	if (!Length)
	{
		return;
	}

	double NormalizedX = DirectionX / Length;
	double NormalizedY = DirectionY / Length;

	Position.x += (int)(NormalizedX * Speed);
	Position.y += (int)(NormalizedY * Speed);

	if (Position.x < 0)
	{
		Position.x = 0;
	}

	if (Position.y < 0)
	{
		Position.y = 0;
	}

	if (Position.x > WINDOW_WIDTH - FrameData.FrameLength)
	{
		Position.x = WINDOW_WIDTH - FrameData.FrameLength;
	}

	if (Position.y > WINDOW_HEIGHT - FrameData.FrameHeight - FrameData.ShadowHeight)
	{
		Position.y = WINDOW_HEIGHT - FrameData.FrameHeight - FrameData.ShadowHeight;
	}
}

void APimon::UpdateBullet()
{
	if (BulletList.size() == 0)
	{
		return;
	}

	for (int i = 0; i < BulletList.size(); i++)
	{
		BulletList[i]->Update(i);
	}
}

void APimon::RendAnimationAndBullet()
{
	CurrentShadowAnimation->Rend(CalculateShadowPosition(), 5);
	CurrentAnimation->Rend(Position, 5);

	for (const std::shared_ptr<UBullet>& Bullet : BulletList)
	{
		Bullet->Rend();
	}
}

void APimon::OnDamage()
{
	static TCHAR Text[128];
	_stprintf_s(Text, _T("Final Score: %d"), Score);
	MessageBox(GetHWnd(), Text, _T("Game Over!"), MB_OK);
	bIsGameActivate = false;
}
