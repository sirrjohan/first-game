#include "worldGenerator.h"
#include "randomStuff.h"
#include <iostream>

void generateWorld(GameMap& gameMap, int seed)
{
	const int w = 900;
	const int h = 500;

	gameMap.create(w, h);
	
	int stoneSize = 380;
	int dirtSize = 50;

	std::ranlux24_base rng(seed);

	for (int x = 0; x < w; x++)
	{
		if (stoneSize <= 385 && stoneSize >= 365)
		{
			stoneSize = stoneSize + getRandomInt(rng, -1, 1);
		}else
		
			if (stoneSize > 385)
			{
				stoneSize = stoneSize + getRandomInt(rng, 0, 1);
			}
		else
			if (stoneSize > 425)
			{
				stoneSize = stoneSize + getRandomInt(rng, 0-1, 0);
			}
			else

				if (stoneSize < 365)
				{
					stoneSize = stoneSize + getRandomInt(rng, 1, 2);
				}
				else
					if (stoneSize < 335)
					{
						stoneSize = stoneSize + getRandomInt(rng, 1, 2);
					}

		std::cout << stoneSize << " ";

		for (int y = 0; y < h; y++)
		{
			Block b;

			if ( y < h - (stoneSize + dirtSize ))
			{
				//air
			} 
			else if ( y == h - (stoneSize + dirtSize ))
			{
				b.type = Block::grassBlock;
			}
			else if ( y < h - stoneSize )
			{
				b.type = Block::dirt;
			}
			else
			{
				b.type = Block::stone;

				if (getRandomChance(rng, 0.01))
				{
					b.type = Block::manaOre;
				}
			}
			
			gameMap.getBlockUnsafe(x, y) = b;

		}
	}
}