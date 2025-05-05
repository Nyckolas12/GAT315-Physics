#include "PolarScene.h"

void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{

	m_camera->BeginMode();
	DrawGrid(10, 5, WHITE);
	//float radius = 3;
	float rate = 0.2f;
	float time = GetTime() * rate;
	int steps = 100;
	// Archimedean Spiral
	for (int i = 0; i < steps; i++)
	{
		float a = 1.0f; // starting distance from origin 
		float b = 0.5f; // distance betweeen turns
		float theta = (i/ (float) steps) * (1.4 * PI);
		float radius = a + b * theta;
		Polar polar(theta, radius);
		Vector2 pos = polar;

		//DrawCircle(pos, 0.25, RED);
	}

	//Cardioid
	for (int i = 0; i < steps; i++)
	{
		float a = 1.5f;
		float theta = time + (i / (float)steps) * (2 * PI);
		float radius = a * (0.5f + cosf(theta));
		Polar polar(theta, radius);
		Vector2 pos = polar;

		//DrawCircle(pos, 0.1f, RED);
	}


	// Limacon
	for (int i = 0; i < steps; i++)
	{
		float a = 1.0f; // starting distance from origin 
		float b = 5.0f; // distance betweeen turns
		float theta = time + (i / (float)steps) * (3 * PI);
		float radius = a + b * cosf(theta);
		Polar polar(theta, radius);
		Vector2 pos = polar;

		//DrawCircle(pos, 0.25, RED);
	}

	// Rose Curve
	for (int i = 0; i < steps; i++)
	{
		float a = 4.0f; // starting distance from origin 
		float b = -2.0f; // distance betweeen turns
		float theta = time + (i / (float)steps) * (3 * PI);
		float radius = a *cosf(b* theta);
		float radiusin = a * sinf(b* theta);
		Polar polar(theta, radiusin);
		Vector2 pos = polar;

		//DrawCircle(pos, 0.25, RED);
	}

	//Fermat't Spiral
	for (int i = 0; i < steps; i++)
	{
		float a = 1.0f; // starting distance from origin 
		float theta =  (i / (float)steps) * (1.4 * PI);
		float radius = a * sqrtf(theta);
		
		Polar polar(theta, radius);
		Vector2 pos = polar;
		

		DrawCircle(pos, 0.25, RED);
	}

	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}
