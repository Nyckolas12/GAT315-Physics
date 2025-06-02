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
	
	if (IsKeyPressed(KEY_SPACE)) World::simulate = !World::simulate;

	if (!GUI::mouseOverGUI)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL)))
		{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		Body::Type type = (Body::Type)GUI::bodyTypeActive;

		Body* body = m_world->CreateBody(type,position,GUI::massValue, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

		body->restitution = GUI::restitutionValue;
		body->gravityScale = GUI::gravityScaleValue;
		body->damping = GUI::dampingValue;

		body->ApplyForce(randomOnUnitCircle() * 32, Body::ForceMode::Velocity);

		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}

		if (m_selectedBody)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL))
			{
				if (m_selectedBody->type == Body::Type::Dynamic)
				{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				Spring::ApplyForce(position, *m_selectedBody, 0.23f, 15.0f);

				}
			}else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_conncetedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else {
				if (m_selectedBody && m_conncetedBody)
				{
					float distance = Vector2Distance(m_selectedBody->position, m_conncetedBody->position);
					m_world->CreateSpring(m_selectedBody, m_conncetedBody, distance, GUI::stiffnessValue, GUI::dampingValue);
				}

				m_selectedBody = nullptr;
				m_conncetedBody = nullptr; 
			}
		}

		if (GUI::resetPressed) m_world->DestroyAll();
		
	}
	

	//apply collision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -GUI::restitutionValue;

		}

		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -GUI::restitutionValue;
		}

		
	}

	GUI::Update();
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


