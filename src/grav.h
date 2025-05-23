#pragma once
#include "world.h"
#include "raymath.h"


struct Grav
{
    static void ApplyGravitation(bodies_t& bodies, float strength);
};
