#include "MapFile.h"
#include <fstream>
#include <iostream>

MapFile::MapFile(void)
{
}


MapFile::~MapFile(void)
{
}


void MapFile::Save(vector<vector<char>> vet, char* name){

   int n = vet.size(); 
   int m = vet[0].size();

	ofstream out(name, ios::out);
	out << n << " " << m << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			out << vet[i][j] << " ";
		out << endl;
	}
	out.close();
}


vector<vector<char>> MapFile::Load(char* name){
	int n = 0;
	int m = 0;

	vector<vector<char>> vet;

	ifstream in(name, ios::in);
	
	in >> n >> m;

	for (int i = 0; i < n; i++){
		vector<char> v;
		for (int j = 0; j < m; j++){
			char a;
			in >> a;
			v.push_back(a);
		}

		vet.push_back(v);
	}
	
	in.close();

  return vet;
}