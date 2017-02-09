#include "LoadTetGenFiles.h"


LoadTetGenFiles::LoadTetGenFiles(string file0, string file1, string file2) : node_file_name(file0), ele_file_name(file1), face_file_name(file2)
{
	this->LoadNodeFile();
	this->LoadEleFile();
	this->loadFaceFile();
	//this->DisplayInfo();
}


LoadTetGenFiles::LoadTetGenFiles(string node_file, string face_file) : node_file_name(node_file), face_file_name(face_file)
{
	this->LoadNodeFile();
	this->loadFaceFile();
	this->_createSpringsFromFaceFile();
}


LoadTetGenFiles::~LoadTetGenFiles()
{
}


vector<Vector3f> LoadTetGenFiles::LoadNodeFile() {
	/* Load the node info file. */
	fstream node_file_stream;
	string string_value;
	istringstream iss;
	size_t info;
	float x, y, z;

	node_file_stream.open(this->node_file_name);
	if (node_file_stream.fail()) {
		/* This error message will show up when the console window is opened for debugging. */
		cerr << "[LoadTetGenFiles.cpp: LoadNodeFile()] Error: Open TetGen node file failed." << endl;
		system("Pause");
		//exit(1);
	}

	getline(node_file_stream, string_value);
	iss.clear();
	iss.str(string_value);
	iss >> this->particles_num;
	this->starting_positions.resize(this->particles_num);

	while (getline(node_file_stream, string_value)) {
		iss.clear();
		iss.str(string_value);

		if (string_value[0] != FILE_COMMENT) {
			iss >> info;
			iss >> x;
			iss >> y;
			iss >> z;

			this->starting_positions[info].set(Vector3f(x, y + 22.0f, z));
		}
	}

	node_file_stream.close();
	return this->starting_positions;
}


vector<Vector2f> LoadTetGenFiles::LoadEleFile() {
	/* Load the tetrahedrons element info file. */
	fstream ele_file_stream;
	string string_value;
	istringstream iss;
	size_t info;
	float p0, p1, p2, p3;
	list<Vector2f>::iterator it = this->raw_springs_list.begin();

	ele_file_stream.open(this->ele_file_name);
	if (ele_file_stream.fail()) {
		/* This error message will show up when the console window is opened for debugging. */
		cerr << "[LoadTetGenFiles.cpp: LoadEleFile()] Error: Open TetGen element file failed." << endl;
		system("Pause");
		//exit(1);
	}

	getline(ele_file_stream, string_value);
	iss.clear();
	iss.str(string_value);
	iss >> this->tetrahedrons_num;

	while (getline(ele_file_stream, string_value)) {
		iss.clear();
		iss.str(string_value);

		if (string_value[0] != FILE_COMMENT) {
			iss >> info;
			iss >> p0;
			iss >> p1;
			iss >> p2;
			iss >> p3;

			this->raw_springs_list.insert(it, Vector2f(p0, p1));
			this->raw_springs_list.insert(it, Vector2f(p1, p2));
			this->raw_springs_list.insert(it, Vector2f(p0, p2));
			this->raw_springs_list.insert(it, Vector2f(p0, p3));
			this->raw_springs_list.insert(it, Vector2f(p1, p3));
			this->raw_springs_list.insert(it, Vector2f(p2, p3));
		}
	}

	ele_file_stream.close();

	this->raw_springs_list.sort();
	this->raw_springs_list.unique();

	this->springs_num = raw_springs_list.size();

	//Currently it does not have redundant information.
	this->starting_springs = TransListToArray(this->raw_springs_list);
	return this->starting_springs;
}


//Basically doing the same job as loadNodeFile().
vector<Vector3f> LoadTetGenFiles::loadFaceFile() {
	fstream face_file_stream;
	string string_value;
	istringstream iss;
	size_t info;
	float x, y, z;

	face_file_stream.open(this->face_file_name);
	if (face_file_stream.fail()) {
		/* This error message will show up when the console window is opened for debugging. */
		cerr << "[LoadTetGenFiles.cpp: loadFaceFile()] Error: Open TetGen face file failed." << endl;
		system("Pause");
		//exit(1);
	}

	getline(face_file_stream, string_value);
	iss.clear();
	iss.str(string_value);
	iss >> this->face_num;
	this->faces.resize(this->face_num);

	while (getline(face_file_stream, string_value)) {
		iss.clear();
		iss.str(string_value);

		if (string_value[0] != FILE_COMMENT) {
			iss >> info;
			iss >> x;
			iss >> y;
			iss >> z;

			this->faces[info].set(Vector3f(x, y, z));
		}
	}

	face_file_stream.close();
	return this->faces;
}


void LoadTetGenFiles::_createSpringsFromFaceFile() {
	list<Vector2f> springs;
	list<Vector2f>::iterator it = springs.begin();

	for (size_t i = 0; i < this->faces.size(); i++) {
		float p0 = this->faces[i].x();
		float p1 = this->faces[i].y();
		float p2 = this->faces[i].z();

		springs.insert(it, Vector2f(p0, p1));
		springs.insert(it, Vector2f(p1, p2));
		springs.insert(it, Vector2f(p0, p2));
	}

	springs.sort();
	springs.unique();
	this->springs_num = springs.size();
	this->starting_springs = TransListToArray(springs);
}


vector<Vector2f> LoadTetGenFiles::TransListToArray(list<Vector2f> clean_springs_list) {
	list<Vector2f>::iterator it = clean_springs_list.begin();
	size_t size = clean_springs_list.size();
	vector<Vector2f> my_array;
	my_array.resize(size);

	for (size_t i = 0; i < size; i++, it++) {
		my_array[i].set(*it);
		
		if (it == clean_springs_list.end()) it--;
	}

	return my_array;
}


void LoadTetGenFiles::DisplayInfo() {
	cout << "particles_num: " << this->particles_num << endl;
	cout << "springs_num: " << this->springs_num << endl;

	for (size_t i = 0; i < this->particles_num; i++) {
		cout << "particle[" << i << "]: " << this->starting_positions[i].getX() << ", " << this->starting_positions[i].getY() << ", " << this->starting_positions[i].getZ() << endl << endl;
	}

	for (size_t i = 0; i < this->springs_num; i++) {
		cout << "spring[" << i << "]: " << this->starting_springs[i].x() << ", " << this->starting_springs[i].y() << endl << endl;
	}
}