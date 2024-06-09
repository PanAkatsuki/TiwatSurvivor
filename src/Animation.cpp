#include "Animation.h"

// Constructor
Animation::Animation(Atlas* atlas, int interval)
{
	m_Atlas = atlas;
	interval_ms = interval;
	timer = 0;
	idxFrame = 0;
}
Animation::~Animation()
{

}

// Rend
void Animation::PutImageAlpha(int x, int y, IMAGE* img) const
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}
void Animation::Rend(int x, int y, int delta)
{
	timer += delta;
	if (timer >= interval_ms)
	{
		idxFrame = (idxFrame + 1) % m_Atlas->m_FrameList.size();
		timer = 0;
	}
	PutImageAlpha(x, y, m_Atlas->m_FrameList[idxFrame]);
}