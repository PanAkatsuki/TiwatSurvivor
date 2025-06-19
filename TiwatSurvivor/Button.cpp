#include "Button.h"

UButton::UButton(std::shared_ptr<FButtonImageSet> InButtonImageSet)
	: ButtonImageSet(InButtonImageSet)
{
	Status = EButtonStatus::Idle;

	ButtonFrameData.Width = InButtonImageSet->IdleImage->getwidth();
	ButtonFrameData.Height = InButtonImageSet->IdleImage->getheight();
}

UButton::~UButton()
{
}

bool UButton::CheckCursorHit(int x, int y)
{
	return x >= Region.left && x <= Region.right &&
		y >= Region.top && y <= Region.bottom;
}

void UButton::ProcessEvent(const ExMessage& Message)
{
	switch (Message.message)
	{
	case WM_MOUSEMOVE:
		if (Status == EButtonStatus::Idle && CheckCursorHit(Message.x, Message.y))
		{
			Status = EButtonStatus::Hovered;
		}
		else if (Status == EButtonStatus::Hovered && !CheckCursorHit(Message.x, Message.y))
		{
			Status = EButtonStatus::Idle;
		}
		break;
	case WM_LBUTTONDOWN:
		if (Status == EButtonStatus::Hovered)
		{
			Status = EButtonStatus::Pushed;
		}
		break;
	case WM_LBUTTONUP:
		if (Status == EButtonStatus::Pushed)
		{
			OnClick();
		}
		break;
	}
}

void UButton::Rend()
{
	switch (Status)
	{
	case EButtonStatus::Idle:
		putimage(Region.left, Region.top, ButtonImageSet->IdleImage.get());
		break;
	case EButtonStatus::Hovered:
		putimage(Region.left, Region.top, ButtonImageSet->HoveredImage.get());
		break;
	case EButtonStatus::Pushed:
		putimage(Region.left, Region.top, ButtonImageSet->PushedImage.get());
		break;
	}
}

UStartButton::UStartButton(std::shared_ptr<FButtonImageSet> InButtonImageSet)
	: UButton(InButtonImageSet)
{
	Region.left = (WINDOW_WIDTH - ButtonFrameData.Width) / 2;
	Region.right = Region.left + ButtonFrameData.Width;
	Region.top = 430;
	Region.bottom = Region.top + ButtonFrameData.Height;
}

UStartButton::~UStartButton()
{
}

void UStartButton::OnClick()
{
	bIsGameStarted = true;
	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
}

UQuitButton::UQuitButton(std::shared_ptr<FButtonImageSet> InButtonImageSet)
	: UButton(InButtonImageSet)
{
	Region.left = (WINDOW_WIDTH - ButtonFrameData.Width) / 2;
	Region.right = Region.left + ButtonFrameData.Width;
	Region.top = 550;
	Region.bottom = Region.top + ButtonFrameData.Height;
}

UQuitButton::~UQuitButton()
{
}

void UQuitButton::OnClick()
{
	bIsGameActivate = false;
}