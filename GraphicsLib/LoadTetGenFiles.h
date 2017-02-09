#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <Vector3.h>
#include <Vector2.h>

using namespace std;

static const char FILE_COMMENT = '#';

class LoadTetGenFiles
{
public:
	LoadTetGenFiles(string file0, string file1, string file2);

	//Auto Calculate the springs' info only by using .face file.
	LoadTetGenFiles(string node_file, string face_file);
	~LoadTetGenFiles();

	vector<Vector3f> LoadNodeFile();
	vector<Vector2f> LoadEleFile();
	vector<Vector3f> loadFaceFile();

	void _createSpringsFromFaceFile();
	vector<Vector2f> TransListToArray(list<Vector2f> clean_springs_list);
	void DisplayInfo();

public:
	string node_file_name, ele_file_name, face_file_name;
	size_t particles_num, tetrahedrons_num, springs_num, face_num;

	vector<Vector3f> starting_positions;
	list<Vector2f> raw_springs_list;
	vector<Vector2f> starting_springs;
	vector<Vector3f> faces;
};

