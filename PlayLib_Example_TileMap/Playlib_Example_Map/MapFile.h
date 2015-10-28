#pragma once
#include <vector>
using namespace std;

class MapFile
{
public:
	MapFile(void);
	~MapFile(void);
	vector<vector<char>> Load(char* name);
	void Save(vector<vector<char>> vet, char* name);
};

