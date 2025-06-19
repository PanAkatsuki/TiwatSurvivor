#include "Atlas.h"

#include "TiwatSurvivorFunctionLibrary.h"

UAtlas::UAtlas(LPCTSTR InPath, int InNum)
{
	TCHAR PathFile[256] = {};
	for (size_t i = 0; i < InNum; i++)
	{
		_stprintf_s(PathFile, InPath, i);

		std::shared_ptr<IMAGE> Frame = std::make_shared<IMAGE>();
		loadimage(Frame.get(), PathFile);

		FrameList.push_back(Frame);
	}
}

UAtlas::~UAtlas()
{
}

