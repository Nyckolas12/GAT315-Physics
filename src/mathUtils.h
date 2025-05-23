#pragma once
#include <cstdlib>
#include <algorithm>

inline float randomf()
{
	return rand() / (float)RAND_MAX;
}

inline float randomf(float max)
{
	return randomf() * max;
}

inline float randomf(float min,float max)
{
	if(min > max) std::swap(min, max);
	return min +( randomf() *(max- min));
}

inline float DegToRad(float degrees)
{
	return degrees * (PI / 180);
}

inline float RadToDeg(float radians)
{
	return radians * (180 / PI);
}

inline float Vector2Length(const Vector2& v)
{

	return sqrtf(v.x * v.x + v.y * v.y);
}