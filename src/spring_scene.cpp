#include "vector_scene.h"
#include "body.h"
#include "raymath.h"
#include "raygui.h"
#include "mathUtils.h"
#include "world.h"
#include "grav.h"
#include "gui.h"
#include "spring_scene.h"

#define GUI_DATA(data) TextFormat("%0.2f", data), &data;

void SpringScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });
	m_world = new World();
	m_world->Initialize();
	
}

void SpringScene::Update()
{
	float dt = GetFrameTime();
	
	if (!GUI::mouseOverGUI && IsMouseButtonPressed(0))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		Body::Type type = (Body::Type)GUI::physicsWindowBoxActive;

		Body* body = m_world->CreateBody(type,position,GUI::massValue, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

		body->restitution = GUI::restitutionValue;
		body->gravityScale = GUI::gravityScaleValue;

		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}

		if (m_selectedBody)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_conncetedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else {
				if (m_selectedBody && m_conncetedBody)
				{
					float distance = Vector2Distance(m_selectedBody->position, m_conncetedBody->position);
					m_world->CreateSpring(m_selectedBody, m_conncetedBody, distance, 20);
				}

				m_selectedBody = nullptr;
				m_conncetedBody = nullptr; 
			}
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

void SpringScene::FixedUpdated()
{
	
	m_world->Step(Scene::fixedTimeStep);
}

void SpringScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, BLUE);
	m_world->Draw(*this);
	if (m_selectedBody)
	{

		DrawCircleLine(m_selectedBody->position, m_selectedBody->size, YELLOW, 5);
		if (m_conncetedBody)
		{
			DrawCircleLine(m_conncetedBody->position, m_conncetedBody->size, YELLOW, 5);
			DrawLine(m_selectedBody->position, m_conncetedBody->position, 3, GREEN);
		}
		else {
			DrawLine(m_selectedBody->position, m_camera->ScreenToWorld(GetMousePosition()), 3, RED);
		}
	}
	m_camera->EndMode();
}

void SpringScene::DrawGUI()

{
	GUI::Draw();
}


