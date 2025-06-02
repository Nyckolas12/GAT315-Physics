#include "world.h"
#include "grav.h"
#include "body.h"
#include "gui.h"
#include "collision.h"



World::~World()
{
}

void World::Initialize(Vector2 gravity, size_t poolSize)
{
    World::gravity = gravity;
    m_bodies.reserve(poolSize);

}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{
    Body* body = new Body(position, size, color);
    m_bodies.push_back(body);

    return body;
}

Body* World::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color)
{
    Body* body = new Body(type, position, mass, size, color);
    m_bodies.push_back(body);

    return body;
}

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float k, float damping)
{
    Spring* spring = new Spring(bodyA, bodyB, restLength, k, damping);
    m_spring.push_back(spring);
    return spring;
}

void World::Step(float timestep)
{
    if (!simulate) return;
   

    if (gravitation > 0) Grav::ApplyGravitation(m_bodies, gravitation);

    for (auto spring : m_spring)
    {
        spring->ApplyForce(springStiffnessMultiplier);
    }

    for (auto body : m_bodies)
    {
        body->Step(timestep);
        body->ClearForce();
    }

    for (int i = 0; i < 10; i++)
    {
    Collision::CreateContacts(m_bodies, m_contacts);
    Collision::SeparateContacts(m_contacts);
    Collision::ResolveContacts(m_contacts);
    m_contacts.clear();

    }
}

void World::Draw(const Scene& scene)
{

    for (auto spring : m_spring)
    {
        spring->Draw(scene);
    }
    for (auto body : m_bodies)
    {
        body->Draw(scene);
    }
}

void World::DestroyAll()
{
    for (auto body : m_bodies)
    {
        delete body;
    }
    m_bodies.clear();
    for (auto spring : m_spring)
    {
        delete spring;
    }
    m_spring.clear();

}