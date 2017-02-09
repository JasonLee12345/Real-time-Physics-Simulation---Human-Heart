#include "Grid.h"

//const static unsigned int POSITION_LOC = 0;
//const static unsigned int COLOR_LOC = 0;
#define POSITION_LOC 0
#define COLOR_LOC 1

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Grid::Grid() :
vboId(0),
shader(nullptr)
{
	std::srand(time(NULL));
}


Grid::~Grid()
{
}


void Grid::loadShader(const string& vertexShader, const string& fragmentShader) {
	this->shader = make_shared<Shader>();
	this->shader->load(vertexShader, fragmentShader);

	this->shader->compile();
	this->shader->link();
	glBindAttribLocation(this->shader->getProgramID(), POSITION_LOC, "position");
	glBindAttribLocation(this->shader->getProgramID(), COLOR_LOC, "color");
}


void Grid::constructGrid(const Color3f &color, float y, float x_min, float x_max, float z_min, float z_max) {
	GridVertex vert;
	float r = color.getR();
	float g = color.getG();
	float b = color.getB();

	vert.position = Vector3f(x_min, y, z_min);
	vert.color = Color3f(r + Random(0.0f, 0.2f), g + Random(0.0f, 0.2f), b + Random(0.0f, 0.2f));
	this->vertices.push_back(vert);

	vert.position = Vector3f(x_max, y, z_min);
	vert.color = Color3f(r + Random(0.0f, 0.2f), g + Random(0.0f, 0.2f), b + Random(0.0f, 0.2f));
	this->vertices.push_back(vert);

	vert.position = Vector3f(x_max, y, z_max);
	vert.color = Color3f(r + Random(0.0f, 0.2f), g + Random(0.0f, 0.2f), b + Random(0.0f, 0.2f));
	this->vertices.push_back(vert);

	vert.position = Vector3f(x_min, y, z_max);
	vert.color = Color3f(r + Random(0.0f, 0.2f), g + Random(0.0f, 0.2f), b + Random(0.0f, 0.2f));
	this->vertices.push_back(vert);

	this->constructOnGPU();
}


void Grid::constructOnGPU() {
	glGenBuffers(1, &this->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GridVertex), &this->vertices[0], GL_STATIC_DRAW);
}


void Grid::beginRender() {
	if (this->shader != nullptr)
		this->shader->enable();

	glBindBuffer(GL_ARRAY_BUFFER, this->vboId);

	glEnableVertexAttribArray(POSITION_LOC);
	glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(GridVertex), BUFFER_OFFSET(0));

	glEnableVertexAttribArray(COLOR_LOC);
	glVertexAttribPointer(COLOR_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(GridVertex), BUFFER_OFFSET(3 * sizeof(float)));

	//glDrawArrays(GL_LINES, 0, this->vertices.size());
	/*unsigned int ind[] = { 0, 1, 2,
							0, 2, 3 };*/
	vector<unsigned int> ind;
	ind.push_back(0); ind.push_back(1); ind.push_back(2);
	ind.push_back(0); ind.push_back(2); ind.push_back(3);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ind);
	glDrawRangeElements(GL_TRIANGLES, 0, 2, 3, GL_UNSIGNED_INT, &ind[0]);
	glDrawRangeElements(GL_TRIANGLES, 0, 3, 3, GL_UNSIGNED_INT, &ind[3]);
}


void Grid::endRender() {
	if (this->shader != nullptr)
		this->shader->disable();

	glDisableVertexAttribArray(POSITION_LOC);
	glDisableVertexAttribArray(COLOR_LOC);
	glDeleteBuffers(1, &this->vboId);
}


shared_ptr<Shader>& Grid::getShader() {
	return this->shader;
}


float Grid::Random(float lower, float upper) {
	int r = rand();
	float fraction = ((float)r / RAND_MAX) * (upper - lower);
	float x = lower + fraction;
	return x;
}


/* Generate a random color based on baseColor. */
Color3f Grid::RandomColor(const Color3f& baseColor) {
	float r = baseColor.r() + Random(0.0f, 0.8f);
	float g = baseColor.g() + Random(0.0f, 0.8f);
	float b = baseColor.b() + Random(0.0f, 0.8f);
	return Color3f(r, g, b);
}