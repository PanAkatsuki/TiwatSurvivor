#include "PlayerController.h"

#include "Pimon.h"


APlayerController::APlayerController()
{
}

APlayerController::~APlayerController()
{
}

void APlayerController::ProcessEvent(const ExMessage& Message)
{
	if (Message.message == WM_KEYDOWN)
	{
		switch (Message.vkcode)
		{
		case VK_UP:
			bIsMoveUp = true;
			break;
		case VK_DOWN:
			bIsMoveDown = true;
			break;
		case VK_LEFT:
			bIsMoveLeft = true;
			break;
		case VK_RIGHT:
			bIsMoveRight = true;
			break;
		default:
			break;
		}
	}
	else if (Message.message == WM_KEYUP)
	{
		switch (Message.vkcode)
		{
		case VK_UP:
			bIsMoveUp = false;
			break;
		case VK_DOWN:
			bIsMoveDown = false;
			break;
		case VK_LEFT:
			bIsMoveLeft = false;
			break;
		case VK_RIGHT:
			bIsMoveRight = false;
			break;
		default:
			break;
		}
	}

	if (bIsMoveLeft)
	{
		Owner->SetDirection(EDirection::left);
	}
	else if (bIsMoveRight)
	{
		Owner->SetDirection(EDirection::right);
	}
}

