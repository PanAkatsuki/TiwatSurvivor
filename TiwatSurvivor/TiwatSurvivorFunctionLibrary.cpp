#include "TiwatSurvivorFunctionLibrary.h"

#include "EnemyBoar.h"
#include "StructType.h"

void UTiwatSurvivorFunctionLibrary::TryGenerateEnemyBoar(std::vector<std::shared_ptr<AEnemy>>& InEnemyList, const FAtlasSet& InAtlasSet, const int InInterval)
{
	static int Counter = 0;
	if ((++Counter) % InInterval == 0)
	{
		InEnemyList.push_back(std::make_shared<AEnemyBoar>(InAtlasSet));
		Counter = 0;
	}
}

void UTiwatSurvivorFunctionLibrary::DrawPlayScore(int InScore)
{
	static TCHAR Text[64];
	_stprintf_s(Text, _T("Score: %d"), InScore);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	outtextxy(WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100, Text);
}

std::shared_ptr<IMAGE> UTiwatSurvivorFunctionLibrary::FlipImage(std::shared_ptr<IMAGE> InImage)
{
	const int Width = InImage->getwidth();
	const int Height = InImage->getheight();

	std::shared_ptr<IMAGE> NewImage = std::make_shared<IMAGE>();
	Resize(NewImage.get(), Width, Height);

	DWORD* InImageColorBuffer = GetImageBuffer(InImage.get());
	DWORD* NewImageColorBuffer = GetImageBuffer(NewImage.get());
	
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			int ImImageColorBufferIndex = y * Width + x;
			int NewImageColorBufferIndex = y * Width + Width - 1 - x;
			NewImageColorBuffer[NewImageColorBufferIndex] = InImageColorBuffer[ImImageColorBufferIndex];
		}
	}

	return NewImage;
}

std::shared_ptr<IMAGE> UTiwatSurvivorFunctionLibrary::SketchImage(std::shared_ptr<IMAGE> InImage)
{
	const int Width = InImage->getwidth();
	const int Height = InImage->getheight();

	std::shared_ptr<IMAGE> NewImage = std::make_shared<IMAGE>();
	Resize(NewImage.get(), Width, Height);

	DWORD* InImageColorBuffer = GetImageBuffer(InImage.get());
	DWORD* NewImageColorBuffer = GetImageBuffer(NewImage.get());

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			int Index = y * Width + x;
			if ((InImageColorBuffer[Index] & 0xFF000000) >> 24)
			{
				NewImageColorBuffer[Index] = BGR(RGB(255, 255, 255)) | (((DWORD)(BYTE)(255)) << 24);
			}
		}
	}

	return NewImage;
}

std::shared_ptr<IMAGE> UTiwatSurvivorFunctionLibrary::BlendImage(std::shared_ptr<IMAGE> InOriginalImage, std::shared_ptr<IMAGE> InBlendImage, float InRadio)
{
	const int Width = InOriginalImage->getwidth();
	const int Height = InOriginalImage->getheight();

	std::shared_ptr<IMAGE> NewImage = std::make_shared<IMAGE>();

	DWORD* OriginalImageColorBuffer = GetImageBuffer(InOriginalImage.get());
	DWORD* BlendImageColorBuffer = GetImageBuffer(InBlendImage.get());
	DWORD* NewImageColorBuffer = GetImageBuffer(NewImage.get());

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			int Index = y * Width + x;

			if ((OriginalImageColorBuffer[Index] & 0xFF000000) >> 24)
			{
				// Order is different, Should Change position of R and B
				BYTE R = (BYTE)(GetBValue(OriginalImageColorBuffer[Index]) * InRadio + GetBValue(BlendImageColorBuffer[Index]) * (1 - InRadio));
				BYTE G = (BYTE)(GetGValue(OriginalImageColorBuffer[Index]) * InRadio + GetGValue(BlendImageColorBuffer[Index]) * (1 - InRadio));
				BYTE B = (BYTE)(GetRValue(OriginalImageColorBuffer[Index]) * InRadio + GetRValue(BlendImageColorBuffer[Index]) * (1 - InRadio));

				NewImageColorBuffer[Index] = BGR(RGB(R, G, B)) | (((DWORD)(BYTE)(255)) << 24);
			}
		}
	}

	return NewImage;
}
