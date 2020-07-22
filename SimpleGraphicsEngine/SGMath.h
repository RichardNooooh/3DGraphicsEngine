#pragma once

struct Vector3D 
{
	float x, y, z;
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {};
	
	Vector3D operator+(Vector3D other) 
	{
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

	Vector3D operator-(Vector3D other)
	{
		return Vector3D(x - other.x, y - other.y, z - other.z);
	}

};