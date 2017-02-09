#pragma once

#include <vector>
#include "Shader.h"
#include "Color3.h"

using namespace std;

struct GridVertex {
	Vector3f position;
	Color3f color;
};

class Grid
{
public:
	Grid();
	~Grid();

	void loadShader(const std::string& vertexShader, const std::string& fragmentShader);

	/* Row lines are along the x axis. Column lines are along the z axis. */
	void constructGrid(const Color3f &color, float y, float x_min, float x_max, float z_min, float z_max);

	void beginRender();
	void endRender();

	shared_ptr<Shader>& getShader();

	static float Random(float lower, float upper);
	static Color3f RandomColor(const Color3f& baseColor);

protected:
	void constructOnGPU();

protected:
	shared_ptr<Shader> shader;
	vector<GridVertex> vertices;
	unsigned int vboId;
};

