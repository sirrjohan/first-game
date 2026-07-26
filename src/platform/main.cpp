#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlimgui.h> 
#include <gameMain.h>


int main()
{

#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE);
#endif 

	int maxX = 900;
	int maxY = 450;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(maxX, maxY, "tout sauf le bac fr");
	SetExitKey(KEY_NULL); // disable esc from closing window
	SetTargetFPS(60);



	if (!initGame())
	{
		return 0;
	}

#pragma region imgui
	rlImGuiSetup(true);
		ImGuiIO& io = ImGui::GetIO();
		////io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;       // Enable gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // enable docking
		io.FontGlobalScale = 1.5; // size
#pragma endregion

	while (!WindowShouldClose())
	{
		BeginDrawing();

#pragma region imgui
		rlImGuiBegin();

		//docking stuff......
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

#pragma endregion

		if (!updateGame())
		{
			CloseWindow();
		}

#pragma region imgui
		ImGui::Begin("test fps");
		static float fps = 5;

		ImGui::Text("presets");

		if (ImGui::Button("60 fps"))
		{
			std::cout << "target fps set to 60\n";
			fps = 60;
			SetTargetFPS(fps);
		}
		ImGui::SameLine();
		if (ImGui::Button("600 fps"))
		{
			std::cout << "target fps set to 600\n";
			fps = 600;
			SetTargetFPS(fps);
		}

		

		ImGui::Text("custom");
		ImGui::Separator();
		ImGui::NewLine();

		ImGui::SliderFloat("slider for custom fps", &fps, 5, 1000);
		ImGui::NewLine();

		/*
		ImGui::Text("camera");
		ImGui::Separator();
		ImGui::NewLine();

		ImGui::SliderFloat("slider for custom zoom", &gameData.camera.zoom, 100.0f , 1000.0f);
		ImGui::NewLine();
		*/

		if (ImGui::Button("show fps"))
		{
			std::cout << "fps value :\n"<< fps;
		}


		ImGui::End();

		//ImGui::ShowDemoWindow();
#pragma endregion

		rlImGuiEnd();
		EndDrawing();
	}


	rlImGuiShutdown();
	CloseWindow();
	closeGame();
}

 /*void trash()
{
	//std::cout << "yop";

//changement de tour
/*
if ((j % 2) == 0)
{
	y = (500 - 150);
	x = (900 - 150);
}

if (!(j % 2 == 0))
{
	y = 0;
	x = 0;
	otherturn = true;
}
*/

//mouvement
/*
	if ((i != 2) && otherturn)
	{
		x += 1;
	}
	else if ((i != 2) && !otherturn)
	{
		x -= 1;
	}



	if ((i == 2) && otherturn)
	{
		y += 1;
	}
	else if ((i == 2) && !otherturn)
	{
		y -= 1;
	}

	//remise au bonne endroit

	if (y == 500) {
		y -= y;
		i = 1;
		j++;
	}

	if (x == 900) {
		x -= x;
		i = 2;
		j++;
	}


}
*/