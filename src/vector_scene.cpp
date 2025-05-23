#include "vector_scene.h"
#include "body.h"
#include "raymath.h"
#include "raygui.h"
#include "mathUtils.h"
#include "world.h"
#include "grav.h"
#include "gui.h"
#include <spring_scene.h>
#define GUI_DATA(data) TextFormat("%0.2f", data), &data;

void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });
	m_world = new World();
	m_world->Initialize();
	
}

void VectorScene::Update()
{
	float dt = GetFrameTime();

	if (IsKeyPressed(KEY_SPACE)) World::simulate = !World::simulate;
	
	if (!GUI::mouseOverGUI && IsMouseButtonPressed(0))
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		for (int i = 0; i < 100; i++)
		{
		Body* body = m_world->CreateBody(position, GUI::sizeValue, ColorFromHSV(randomf(360),1,1));
		float theta = randomf(0, 360);
		float offset = randomf(360);
		float x = cosf((theta + offset) * DegToRad(10));
		float y = sinf((theta + offset) * DegToRad(10));
		body->velocity = Vector2{ x , y } * randomf(1,6);
		body->restitution = GUI::restitutionValue;
		body->damping = GUI::dampingValue;
		body->mass = GUI::massValue;
		
		}
	}
	

	//apply collision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -GUI::restitutionValue;

		}

		/*if (body->position.x < -9)
		{
			body->position.x = -9;
			body->position.x *= -body->restitution;
		}

		if (body->position.x < 9)
		{
			body->position.x = 9;
			body->position.x *= -body->restitution;
		}*/
	}
}

void VectorScene::FixedUpdated()
{
	
	m_world->Step(Scene::fixedTimeStep);
}

void VectorScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, BLUE);
	m_world->Draw(*this);
	m_camera->EndMode();
}

void VectorScene::DrawGUI()

{
	GUI::Draw();
}


