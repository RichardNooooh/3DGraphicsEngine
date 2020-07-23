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
	
	Vector3 CrossProduct(Vector3 other) const
	{
		float resultX = y * other.z - z * other.y;
		float resultY = z * other.x - x * other.z;
		float resultZ = x * other.y - y * other.x;

		return Vector3(resultX, resultY, resultZ);
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
		return Vector3(resultX / resultW, resultY / resultW, resultZ / resultW); //Why do we divide by W
	}

};

struct Matrix44 
{
	float m[4][4] = { 0 };
	//Matrix44(float input[4][4]);
	//~Matrix44();

	Matrix44 operator+ (Matrix44 other) const 
	{
		Matrix44 result = { { {0}, {0}, {0}, {0} } };
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				result.m[i][j] = m[i][j] + other.m[i][j];

		return result;
	}

	Matrix44 operator- (Matrix44 other) const
	{
		Matrix44 result = { { {0}, {0}, {0}, {0} } };
		for (int i = 0; i < 4; i++) 
			for (int j = 0; j < 4; j++) 
				result.m[i][j] = m[i][j] - other.m[i][j];

		return result;
	}

	Matrix44 operator* (Matrix44 other) const
	{
		Matrix44 result = { { {0}, {0}, {0}, {0} } };
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				// Inner loop adds left/right entries
				for (int k = 0; k < 4; k++) {
					result.m[i][j] += m[i][k] * other.m[k][j];
				}
			} 
		}
		return { {} };
	}

	Matrix44 Scale(float c) const 
	{
		Matrix44 result = { { {0}, {0}, {0}, {0} } };
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				result.m[i][j] = c * m[i][j];
		return result;
	}

	Matrix44 Transpose() const 
	{
		Matrix44 result = { { {0}, {0}, {0}, {0} } };
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				result.m[i][j] = m[j][i];
		return result;
	}
};

//static const Matrix44 WorldToPerspectiveMatrix = { { {0, 0, 0, 0},
//													 {0, 0, 0, 0},
//													 {0, 0, 0, 0},
//													 {0, 0, 0, 0} } };