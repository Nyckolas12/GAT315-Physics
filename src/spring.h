#pragma once
#include "scene.h"
#include "raylib.h"


struct Spring
{
public:
	struct Body* bodyA;
	struct Body* bodyB;
	float restLength;
	float damping;
	float k; // stiffness

public:
	Spring() = default;
	Spring(Body* bodyA, Body* bodyB, float restLength, float k) :
		bodyA{ bodyA },
		bodyB{ bodyB },
		restLength{ restLength },
		k{ k }
	{
	}

	void ApplyForce(float kMultiplier = 1);
	void Draw(const Scene& scene);
};