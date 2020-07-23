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

	Vector3 Matrix44Multiply(Matrix44 matrix) const 
	{
		float resultX = x * matrix.m[0][0] + y * matrix.m[0][1] + z * matrix.m[0][2];
		float resultY = x * matrix.m[1][0] + y * matrix.m[1][1] + z * matrix.m[1][2];
		float resultZ = x * matrix.m[2][0] + y * matrix.m[2][1] + z * matrix.m[2][2];
		float resultW = x * matrix.m[3][0] + y * matrix.m[3][1] + z * matrix.m[3][2];
		return Vector3(resultX / resultW, resultY / resultW, resultZ / resultW);
	}

};

struct Matrix44 
{
	float m[4][4] = { 0 };
	//Matrix44(float input[4][4]);
	//~Matrix44();

	Matrix44 operator+ (Matrix44 other) const 
	{
		return { { {m[0][0] + other.m[0][0], m[0][1] + other.m[0][1], m[0][2] + other.m[0][3]},
				   {m[1][0] + other.m[1][0], m[1][1] + other.m[1][1], m[1][2] + other.m[1][3]},
				   {m[2][0] + other.m[2][0], m[2][1] + other.m[2][1], m[2][2] + other.m[2][3]},
				   {m[3][0] + other.m[3][0], m[3][1] + other.m[3][1], m[3][2] + other.m[3][3]} } };
	}

	Matrix44 operator- (Matrix44 other) const
	{
		return { { {m[0][0] - other.m[0][0], m[0][1] - other.m[0][1], m[0][2] - other.m[0][3]},
				   {m[1][0] - other.m[1][0], m[1][1] - other.m[1][1], m[1][2] - other.m[1][3]},
				   {m[2][0] - other.m[2][0], m[2][1] - other.m[2][1], m[2][2] - other.m[2][3]},
				   {m[3][0] - other.m[3][0], m[3][1] - other.m[3][1], m[3][2] - other.m[3][3]} } };
	}
};

//static const Matrix44 WorldToPerspectiveMatrix = { { {0, 0, 0, 0},
//													 {0, 0, 0, 0},
//													 {0, 0, 0, 0},
//													 {0, 0, 0, 0} } };