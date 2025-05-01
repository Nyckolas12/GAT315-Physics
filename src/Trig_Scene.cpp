#include "Trig_Scene.h"

void Trig_Scene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });

}

void Trig_Scene::Update()
{
}

void Trig_Scene::Draw()
{
	m_camera->BeginMode();
	DrawCircle(0, 0, 100, RED);
	m_camera->EndMode();
}

void Trig_Scene::DrawGUI()
{
}
