/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <Trig_Scene.h>
#include <PolarScene.h>
#include <vector_scene.h>
#include "spring_scene.h"

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	//Scene* scene = new Trig_Scene("Trig Scene", 1280, 720);
	//Scene* polarScene = new PolarScene("Polar Scene", 1280, 720);
	//Scene* vectorScene = new VectorScene("Vector Scene", 1280, 720);
	Scene* springScene = new SpringScene("Spring Scene", 1280, 720);
	//scene->Initialize();
	//polarScene->Initialize();
	springScene->Initialize();

	SetTargetFPS(60);
	float timeAccum = 0.0f;
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		/*scene->Update();
		scene->BeginDraw();
		scene->Draw();
		scene->EndDraw();*/
		/*polarScene->Update();
		polarScene->BeginDraw();
		polarScene->Draw();
		polarScene->EndDraw();*/

		springScene->Update();
		timeAccum += std::min(GetFrameTime(), 0.5f);
		while (timeAccum >= Scene::fixedTimeStep)
		{
			springScene->FixedUpdated();
			timeAccum -= Scene::fixedTimeStep;
		}
		springScene->BeginDraw();
		springScene->Draw();
		springScene->DrawGUI();
		springScene->EndDraw();


		
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
