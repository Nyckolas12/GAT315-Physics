#include "body.h"
#include "raymath.h"
#include <Integrator.h>
#include "world.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;

	//apply gravity
	force += (World::gravity * gravityScale) * mass;
	//compute acceleration
	acceleration = (force * inveMass);
	
	SemiImplictIntegrator(*this, dt);

	//velocity *= 0.9999f/ (1.0f + (damping * dt));
	//velocity += World::gravity * dt;
	

}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
	//scene.DrawLine(position - velocity, velocity - position, 0.234f, color);
}

void Body::ApplyForce(const Vector2& force)
{
	this->force += force;
}
