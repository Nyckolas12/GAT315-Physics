#include "Trig_Scene.h"

void Trig_Scene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });

}

void Trig_Scene::Update()
{
}

float DegToRad(float degrees)
{
	return degrees * (PI / 180);
}

float RadToDeg(float radians)
{
	return radians * (180 / PI);
}

float Vector2Length(const Vector2& v)
{
	
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector2 Vector2Normalize(const Vector2& v)
{
	float l = Vector2Length(v);
	if (l == 0) return Vector2{ 0,0 };
	return Vector2{ v.x/l, v.y/l };
}

void Trig_Scene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, WHITE);
	//DrawCircle(Vector2{0,0}, 1, RED);
	float radius = 3;
	float rate = 0.2f;
	float time = GetTime() * rate;
	int steps = 30;
	for (int i = 0; i < steps; i++)
	{
		float theta = time + (i / (float)steps) * (2* PI);
		float x = cosf(theta) * radius;
		float y = sinf(theta) * radius;

		DrawCircle(Vector2{x,y}, 0.25, RED);
	}
	//sin /cos
	for (float x = -9.0f; x < 9; x += 0.2)
	{
		float theta = time + (x / 18) * (2 * PI);
		float c = cosf(theta) * radius;
		float s = sinf(theta) * radius;
		DrawCircle(Vector2{ x,c }, 0.25, PURPLE);
		DrawCircle(Vector2{ x,s }, 0.25, BLUE);
	}

	float theta = time;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;
	DrawCircle(Vector2{x,y}, 0.25f, YELLOW );
	float angle = atan2(y,x);
	m_camera->EndMode();
}

void Trig_Scene::DrawGUI()
{
}
