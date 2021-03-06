#include "SGMath.h"

Matrix44 Matrix44::operator+ (Matrix44 other) const
{
	Matrix44 result = { { {0}, {0}, {0}, {0} } };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.m[i][j] = m[i][j] + other.m[i][j];

	return result;
}

Matrix44 Matrix44::operator- (Matrix44 other) const
{
	Matrix44 result = { { {0}, {0}, {0}, {0} } };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.m[i][j] = m[i][j] - other.m[i][j];

	return result;
}

Matrix44 Matrix44::operator* (Matrix44 other) const
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

Matrix44 Matrix44::Scale(float c) const
{
	Matrix44 result = { { {0}, {0}, {0}, {0} } };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.m[i][j] = c * m[i][j];
	return result;
}

Matrix44 Matrix44::Transpose() const
{
	Matrix44 result = { { {0}, {0}, {0}, {0} } };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.m[i][j] = m[j][i];
	return result;
}

Vector3 Vector3::operator+(Vector3 other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(Vector3 other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

float Vector3::DotProduct(Vector3 other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::CrossProduct(Vector3 other) const
{
	float resultX = y * other.z - z * other.y;
	float resultY = z * other.x - x * other.z;
	float resultZ = x * other.y - y * other.x;

	return Vector3(resultX, resultY, resultZ);
}

Vector3 Vector3::Scale(float c) const
{
	return Vector3(c * x, c * y, c * z);
}

Vector3 Vector3::Normal(Vector3 v1, Vector3 v2)
{
	float normX = v1.y * v2.z - v1.z * v2.y;
	float normY = v1.z * v2.x - v1.x * v2.z;
	float normZ = v1.x * v2.y - v1.y * v2.x;
	return Vector3(normX, normY, normZ);
}

Vector3 Vector3::Matrix44Multiply(Matrix44 matrix) const
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
	return Vector3(resultX, resultY, resultZ);
}

float Vector3::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

Triangle::Triangle(Vector3 p0, Vector3 p1, Vector3 p2) : _points{p0, p1, p2}
{
	//Vector3 u = p1 - p0;
	//Vector3 v = p2 - p0;
	//Vector3 normal = Vector3::Normal(u, v);
	//_normal = &normal.Scale(1 / normal.Magnitude());
}
