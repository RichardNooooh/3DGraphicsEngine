#pragma once
#include <math.h>

struct Vector3 
{
	float x, y, z;
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	
	Vector3 operator+(Vector3 other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 operator-(Vector3 other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	float DotProduct(Vector3 other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}
	
	Vector3 Scale(float c) const
	{
		return Vector3(c * x, c * y, c * z);
	}

};