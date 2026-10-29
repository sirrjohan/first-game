#include "worldGenerator.h"
#include "randomStuff.h"
#include <iostream>
#include <cmath>
#include <algorithm>

void generateWorld(GameMap& gameMap, int seed)
{
	const int w = 900;
	const int h = 500;

	gameMap.create(w, h);
	
	int baseStone = 380;
	int stoneSize = baseStone;
	int dirtSize = 50;

	std::ranlux24_base rng(seed);

	// Offsets pour varier les sinusoïdes
	float off1 = getRandomFloat(rng, 0.0f, 6.2831853f);
	float off2 = getRandomFloat(rng, 0.0f, 6.2831853f);

	for (int x = 0; x < w; x++)
	{
		float nx = static_cast<float>(x) / static_cast<float>(w);

		// Relief par superposition d'ondes + léger jitter aléatoire
		float wave =
			std::sinf(nx * 2.0f * 3.1415926f * 0.8f + off1) * 20.0f +  // grandes collines (plus larges / moins hautes)
			std::sinf(nx * 2.0f * 3.1415926f * 3.0f + off2) * 6.0f +   // bosses moyennes (atténuées)
			std::sinf(nx * 2.0f * 3.1415926f * 8.0f) * 2.0f;           // bruit fin (faible)

		int targetStone = baseStone + static_cast<int>(std::round(wave)) + getRandomInt(rng, -1, 1); // jitter réduit

		// Lissage strict : variation max de 1 block par colonne
		int delta = targetStone - stoneSize;
		if (delta > 1) delta = 1;
		if (delta < -1) delta = -1;
		stoneSize += delta;

		// Bornes plus serrées pour empêcher à-coups extrêmes
		stoneSize = std::clamp(stoneSize, 340, 420);

		// Variabilité locale de la couche de terre
		int columnDirt = dirtSize + static_cast<int>(std::round(getRandomFloat(rng, -1.0f, 1.0f)));

		std::cout << stoneSize << " ";

		for (int y = 0; y < h; y++)
		{
			Block b;

			if (y < h - (stoneSize + columnDirt))
			{
				// air
			}
			else if (y == h - (stoneSize + columnDirt))
			{
				b.type = Block::grassBlock;
			}
			else if (y < h - stoneSize)
			{
				b.type = Block::dirt;
			}
			else
			{
				b.type = Block::stone;

				// Quelques minerais plus profonds
				if (getRandomChance(rng, 0.02f) && y > h - stoneSize + 50)
				{
					b.type = Block::manaOre;
				}
			}

			gameMap.getBlockUnsafe(x, y) = b;
		}
	}
}