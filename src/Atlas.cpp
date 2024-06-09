#include "Atlas.h"

Atlas::Atlas(LPCTSTR path, int num)
{
	TCHAR pathFile[256];
	for (size_t i = 0; i < num; i++)
	{
		_stprintf_s(pathFile, path, i);

		IMAGE* frame = new IMAGE();
		loadimage(frame, pathFile, 0, 0, false);
		m_FrameList.push_back(frame);
	}
}
Atlas::~Atlas()
{
	for (size_t i = 0; i < m_FrameList.size(); i++)
	{
		delete m_FrameList[i];
	}
}