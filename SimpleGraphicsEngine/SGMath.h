#pragma once
#include <math.h>

struct Matrix44
{
	float m[4][4];
	//Matrix44(float input[4][4]);
	//~Matrix44();

	Matrix44 operator+ (Matrix44 other) const;

	Matrix44 operator- (Matrix44 other) const;

	Matrix44 operator* (Matrix44 other) const;

	Matrix44 Scale(float c) const;

	Matrix44 Transpose() const;
};

struct Vector3 
{
	float x, y, z;
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	
	Vector3 operator+(Vector3 other) const;

	Vector3 operator-(Vector3 other) const;

	float DotProduct(Vector3 other) const;
	
	Vector3 CrossProduct(Vector3 other) const;

	Vector3 Scale(float c) const;

	Vector3 Matrix44Multiply(Matrix44 matrix) const;
};

struct Triangle
{
	Vector3 _points[3];
	Vector3* _normal = nullptr; //this feels dangerous, as a user can just arbitrarily change this normal... but it gives better performance? Probably?

	Triangle(Vector3 p0, Vector3 p1, Vector3 p2);
};