#include "Bullet.h"

#include "Pimon.h"

#include <time.h>


UBullet::UBullet()
{
}

UBullet::~UBullet()
{
}

void UBullet::Update(int InID)
{
	if (Owner->GetBulletList().size() == 0)
	{
		return;
	}

	clock_t StartTime = clock();

	double RadianInterval = 2 * 3.14159 / Owner->GetBulletList().size();

	double Radius = 100 + 25 * sin(StartTime * RadialSpeed);

	double Radian = StartTime * TangentSpeed + RadianInterval * InID;

	Position.x = Owner->GetPosition().x + Owner->GetFrameDate().FrameLength / 2 + (int)(Radius * cos(Radian));
	Position.y = Owner->GetPosition().y + Owner->GetFrameDate().FrameHeight / 2 + (int)(Radius * sin(Radian));
}

void UBullet::Rend()
{
	setlinecolor(RGB(255, 155, 50));
	setfillcolor(RGB(200, 75, 10));
	fillcircle(Position.x, Position.y, Radius);
}