#pragma once
#include <math.h>


struct Matrix44
{
	float m[4][4];
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

		return result;
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
		float resultX = x * matrix.m[0][0] + y * matrix.m[1][0] + z * matrix.m[2][0] + matrix.m[3][0];
		float resultY = x * matrix.m[0][1] + y * matrix.m[1][1] + z * matrix.m[2][1] + matrix.m[3][1];
		float resultZ = x * matrix.m[0][2] + y * matrix.m[1][2] + z * matrix.m[2][2] + matrix.m[3][2];
		float resultW = x * matrix.m[0][3] + y * matrix.m[1][3] + z * matrix.m[2][3] + matrix.m[3][3];
		if (resultW != 0)
		{
			resultX /= resultW;
			resultY /= resultW;
			resultZ /= resultW;
		}
		/*std::cout << "Multiplied vector, " << x << ", " << y << ", " << z << " to "
			<< resultX << ", " << resultY << ", " << resultZ << "\n";*/
		return Vector3(resultX, resultY, resultZ); //Why do we divide by W
	}
};

struct Triangle 
{
	Vector3 points[3];
};

//static const Matrix44 WorldToPerspectiveMatrix = { { {0, 0, 0, 0},
//													 {0, 0, 0, 0},
//													 {0, 0, 0, 0},
//													 {0, 0, 0, 0} } };