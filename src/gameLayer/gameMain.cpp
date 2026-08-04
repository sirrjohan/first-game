#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlimgui.h> 
#include "gameMain.h"
#include <asserts.h>
#include <assetManager.h>
#include <gameMap.h>
#include <helpers.h>
#include <raymath.h>
#include <difBlocks.h>
#include <worldGenerator.h>


struct GameData
{
	GameMap gameMap;
	Camera2D camera;

}gameData;

AssetManager assetManager;

int selectedBlock = 0;

bool initGame()
{
	assetManager.loadAll();

	generateWorld(gameData.gameMap);


	gameData.camera.target = { 0,0 };
	gameData.camera.rotation = 0.0f;
	gameData.camera.zoom = 45.50f;

	return true;
}



bool updateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5 )
	{
		deltaTime = 1 / 5.f;
	}

	gameData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	ClearBackground({75, 75, 150, 255});

#pragma region
	static float cameraSpeed = 10;

	if (IsKeyDown(KEY_LEFT))  gameData.camera.target.x  -= cameraSpeed * GetFrameTime();
	if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x  += cameraSpeed * GetFrameTime();
	if (IsKeyDown(KEY_UP))    gameData.camera.target.y  -= cameraSpeed * GetFrameTime();
	if (IsKeyDown(KEY_DOWN))  gameData.camera.target.y  += cameraSpeed * GetFrameTime();
#pragma endregion

	Vector2 worldpos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
	int blockX = (int)floor(worldpos.x);
	int blockY = (int)floor(worldpos.y);

	if (IsKeyDown(KEY_W))
	{
		selectedBlock = Block::woodLog;
	}
	
	if (IsKeyDown(KEY_Q))
	{
		selectedBlock = Block::leaves;
	}


	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
		if (b)
		{
			*b = {};
		}
	}
	
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
		if (b)
		{
			b->type = selectedBlock;
		}
	}


	BeginMode2D(gameData.camera);

	Vector2 topLeftView = GetScreenToWorld2D({ 0,0 }, gameData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, gameData.camera);

	int startXView = (int)floorf(topLeftView.x - 1);
	int endXView = (int)ceilf(bottomRightView.x - 1);
	int startYView = (int)floorf(topLeftView.y - 1);
	int endYView = (int)ceilf(bottomRightView.y - 1);

	startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
	endXView = Clamp(endXView, 0, gameData.gameMap.w - 1);

	startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
	endYView = Clamp(endYView, 0, gameData.gameMap.h - 1);


	for (int y = startYView; y <= endYView; y++)
	{
		for (int x = startXView; x <= endXView; x++)
		{
			auto &b = gameData.gameMap.getBlockUnsafe(x, y);


			if (b.type != Block::air && b.type != Block::woodLog)
			{

				DrawTexturePro(
					assetManager.textures,
					getTextureAtlas(b.type, difBlock((uint64_t)x, (uint64_t)y), 32, 32), //source
					{ (float)x, (float)y, 1, 1}, //dest
					{ 0, 0 }, // origin (top left corner)
					0.0f, //rotation
					WHITE //tint
				);

			}

			if (b.type == Block::woodLog)
			{
				auto up = gameData.gameMap.getBlockSafe(x, y-1);
				auto left = gameData.gameMap.getBlockSafe(x-1, y);
				auto right = gameData.gameMap.getBlockSafe(x+1, y);
				auto down = gameData.gameMap.getBlockSafe(x, y + 1);


				if (up && left && right && up->type == Block::leaves && left->type == Block::leaves && right->type == Block::leaves) {
					DrawTexturePro(
						assetManager.woodenTextures,
						getWoodenTextureAtlas(5, difBlock(x, y), 32, 32), //source
						{ (float)x, (float)y, 1, 1 }, //dest
						{ 0, 0 }, // origin (top left corner)
						0.0f, //rotation
						WHITE //tint
					);
				}else 
				if (left && right && left->type == Block::leaves && right->type == Block::leaves) {
					DrawTexturePro(
						assetManager.woodenTextures,
						getWoodenTextureAtlas(1, difBlock(x, y), 32, 32), //source
						{ (float)x, (float)y, 1, 1 }, //dest
						{ 0, 0 }, // origin (top left corner)
						0.0f, //rotation
						WHITE //tint
					);
				} else 
				if (right && right->type == Block::leaves) {
					DrawTexturePro(
						assetManager.woodenTextures,
						getWoodenTextureAtlas(2, difBlock(x, y), 32, 32), //source
						{ (float)x, (float)y, 1, 1 }, //dest
						{ 0, 0 }, // origin (top left corner)
						0.0f, //rotation
						WHITE //tint
					);
				}
				else 
				if (left && left->type == Block::leaves) {
					DrawTexturePro(
						assetManager.woodenTextures,
						getWoodenTextureAtlas(3, difBlock(x, y), 32, 32), //source
						{ (float)x, (float)y, 1, 1 }, //dest
						{ 0, 0 }, // origin (top left corner)
						0.0f, //rotation
						WHITE //tint
					);
				}
				else 
					if (up && down && (up->type != Block::leaves && up->type != Block::air) && down->type != 0 && down->type != Block::woodLog) {
					DrawTexturePro(
						assetManager.woodenTextures,
						getWoodenTextureAtlas(4, difBlock(x, y), 32, 32), //source
						{ (float)x, (float)y, 1, 1 }, //dest
						{ 0, 0 }, // origin (top left corner)
						0.0f, //rotation
						WHITE //tint
					);
				}
				else if (up && down && up->type == Block::air && down->type == Block::woodLog)
				{
					DrawTexturePro(
						assetManager.woodenTextures,
						getWoodenTextureAtlas(6, difBlock(x, y), 32, 32), //source
						{ (float)x, (float)y, 1, 1 }, //dest
						{ 0, 0 }, // origin (top left corner)
						0.0f, //rotation
						WHITE //tint
					);
				}

				else if (up && down && up->type == Block::air && (down->type != Block::woodLog && down->type != Block::air) )
				{
					DrawTexturePro(
						assetManager.woodenTextures,
						getWoodenTextureAtlas(7, difBlock(x, y), 32, 32), //source
						{ (float)x, (float)y, 1, 1 }, //dest
						{ 0, 0 }, // origin (top left corner)
						0.0f, //rotation
						WHITE //tint
					);
				}


				else 
				{
					DrawTexturePro(
						assetManager.woodenTextures,
						getWoodenTextureAtlas(0, difBlock(x, y), 32, 32), //source
						{ (float)x, (float)y, 1, 1 }, //dest
						{ 0, 0 }, // origin (top left corner)
						0.0f, //rotation
						WHITE //tint
					);
				}
			}

		}
	}

	//draw selected block
	DrawTexturePro(
		assetManager.frame,
		{ 0, 0, (float)assetManager.frame.width, (float)assetManager.frame.height}, //source
		{ (float) blockX, (float) blockY, 1, 1 }, //dest
		{ 0, 0 }, // origin (top left corner)
		0.0f, //rotation
		WHITE //tint
	);


	EndMode2D();

#pragma region imgui


	ImGui::Begin("game controll");

	ImGui::SliderFloat("camera zoom", &gameData.camera.zoom, 5, 160);
	ImGui::SliderFloat("camera speed", &cameraSpeed, 5, 60);

	ImGui::End();


#pragma endregion

	DrawFPS(10, 10);

	return true;
}

void closeGame()
{
	std::cout << "\n\nCLOSED!!!!!!!!!\n\n";
}