#include "collision.h"
#include <raymath.h>
#include <mathUtils.h>

void Collision::CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyB = bodies[j];
			if (bodyA->type != Body::Type::Dynamic && bodyB->type != Body::Type::Dynamic) continue;

			if (Intersects(bodyA, bodyB))
			{
				Contact contact;
				contact.bodyA = bodyA;
				contact.bodyB = bodyB;

				Vector2 direction = contact.bodyB->position - contact.bodyA->position;
				float distanceSqr = Vector2LengthSqr(direction);
				if (distanceSqr <= EPSILON)
				{
					direction = Vector2{ randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
					distanceSqr = Vector2LengthSqr(direction);
				}

				float distance = sqrtf(distanceSqr);
				float radius = contact.bodyA->size + contact.bodyB->size;
				contact.depth = (radius + radius) - distance;
				contact.normal = Vector2Normalize(direction);
				contact.restitution = contact.bodyA->restitution / contact.bodyB->restitution;

				contacts.push_back(contact);
			}
		}
	}

}

void Collision::SeparateContacts(contacts_t& contacts)
{
	for (auto contact : contacts)
	{
		float totalInverseMass = contact.bodyA->inveMass + contact.bodyB->inveMass;
		Vector2 separation = contact.normal * (contact.depth / totalInverseMass);
		contact.bodyA->position = contact.bodyA->position + (separation * contact.bodyA->inveMass);
		contact.bodyB->position = contact.bodyB->position + (separation * contact.bodyB->inveMass);
	}


}

bool Collision::Intersects(Body* bodyA, Body* bodyB)
{
	float distance = Vector2Distance(bodyA->position, bodyB->position );
	float radius = bodyA->size + bodyB->size;

	return (distance <= radius);
}
