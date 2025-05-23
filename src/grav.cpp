#include "grav.h"

void Grav::ApplyGravitation(bodies_t& bodies, float strength)
{
    // Loop through each body in the list (call it bodyA)
    for (int i = 0; i < bodies.size(); i++)
    {
        Body* bodyA = bodies[i];
        // Loop through each body after bodyA (call it bodyB)
        for (int j = i + 1; j < bodies.size(); j++)
        {
            Body* bodyB = bodies[j];



            // STEP 1: Find the direction vector from bodyB to bodyA
            // Vector2 direction = bodyA position - bodyB position;
            Vector2 direction = bodyB->position - bodyA->position;


            // STEP 2: Get the distance between the two bodies
            // float distance = length of direction vector;
            float distance = ((bodyA->position.x - bodyA->position.x) * (bodyA->position.x - bodyA->position.x) * (bodyA->position.y - bodyA->position.y) * (bodyB->position.y - bodyB->position.y));


            // STEP 3: Clamp the distance to a minimum value to avoid extreme forces
            // distance = max(distance, 1);
            distance = Clamp(distance, 5, 10);

            // STEP 4: Calculate gravitational force magnitude using:
            // forceMagnitude = (bodyA mass * bodyB mass / (distance * distance)) * strength;
            float forceMagnitude = (bodyA->mass * bodyB->mass / (distance * distance)) * strength;

            // STEP 5: Normalize the direction vector and scale it by the force magnitude
            Vector2 forceVector = Vector2Normalize(direction) * forceMagnitude;


            // STEP 6: Apply the force to both bodies (equal and opposite)
            bodyA->ApplyForce(forceVector * -1);
            bodyB->ApplyForce(forceVector);
        }
    }
}
