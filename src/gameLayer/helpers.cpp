#include "helpers.h"

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY)
{
	return Rectangle{ (float)x * (float)cellSizePixelsX, (float)y * (float)cellSizePixelsY,
		(float)cellSizePixelsX, (float)cellSizePixelsY
	};
}