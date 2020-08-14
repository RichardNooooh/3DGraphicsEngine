#pragma once
#include <string>
#include <fstream>
#include <strstream>
#include <vector>
#include "SGEngine.h"

class SGFileReader 
{
public:
	bool ReadOBJFile(std::string fileName, std::vector<Triangle> *tris);
};