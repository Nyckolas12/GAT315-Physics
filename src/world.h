#pragma once
#include <vector>
#include "raylib.h"
#include "body.h"
#include "spring.h"
#include "contact.h"



using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;
using contacts_t = std::vector<Contact>;
class Scene;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);
	Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color);
	Spring* CreateSpring(Body* bodyA, Body* bodyB, float restLength, float k, float damping);
	void Step(float timestep);
	void Draw(const Scene& scene);

	bodies_t& GetBodies() { return m_bodies; }
	void DestroyAll();

	inline static Vector2 gravity{ 0, -9.82f };
	inline static float gravitation = 0;
	inline static float springStiffnessMultiplier = 1;
	inline static bool simulate = true;


private:
	bodies_t m_bodies;
	springs_t m_spring;
	contacts_t m_contacts;
};