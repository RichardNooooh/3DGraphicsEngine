#include "SGFileReader.h"
#include "SGEngine.h";

bool SGFileReader::ReadOBJFile(std::string fileName, std::vector<Triangle> *tris)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		return false;

	const int charBufferSize = 128;
	std::vector<Vector3> cachedVertices;

	while (!file.eof())
	{
		char line[charBufferSize];
		file.getline(line, charBufferSize);

		std::strstream stringStream;
		stringStream << line;

		char unusedChar;
		switch (line[0]) 
		{
		case 'v':
			float x, y, z;
			stringStream >> unusedChar >> x >> y >> z;
			cachedVertices.push_back(Vector3(x, y, z));
			break;
		case 'f':
			int vIndex0, vIndex1, vIndex2;
			stringStream >> unusedChar >> vIndex0 >> vIndex1 >> vIndex2;
			tris->push_back(Triangle(cachedVertices[vIndex0 - 1], cachedVertices[vIndex1 - 1], cachedVertices[vIndex2 - 1]));
			break;
		}
	}

	return true;
}
