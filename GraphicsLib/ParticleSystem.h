#pragma once

#include "Particle.h"
#include "Spring.h"
#include <vector>
#include <math.h>
#include <memory>
#include <Vector2.h>
#include "Shader.h"
#include "Color3.h"

using namespace std;

#define POSITION_LOC 0
#define COLOR_LOC 1

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct ParticleVertex {
	Vector3f position;
	Color3f color;
};


template <class Real>
class ParticleSystem {
public:
	//Initialize the particle system with the initial value (0, 0, 0) to every particle.
	void initParticleSystem();

	/*
	*	@p_count specifies - how many particles the system has. 
	*	@s_count specifies - how many springs the system has.	*/
	ParticleSystem(size_t p_count, size_t s_count);
	~ParticleSystem();

	//Set the initial values that provided by the user.
	void setParticlesPositions(vector< Vector3<Real> > starting_positions);

	//Set the particles mass for all the particles inside the system. The default is 1.0f.
	void setParticlesMass(Real mass);

	// Deprecated for use.
	//Set springs' connection info. Every springs has two particles connecting each other. 
	//This function will auto help you to set the position info of the spring.
	void setSpringsConnections(vector< vector<size_t> > starting_springs);

	//The overloaded version of the previous one.
	void setSpringsConnections(vector<Vector2f> starting_springs);

	//Set the spring's rest length excatly same with starting length.
	void setSpringsRestLengthsAsStartingLengths();

	//Set the springs' rest length.
	void setSpringsLength(Real length);

	//Set the springs' stiffness. The default value is 20.
	void setSpringsStiffness(Real k);

	//Provide with a fixed variation for every srping.
	void addSpringsRestLength(Real delta);

	/*	Provide with a homogeneous variation.
	 *	@ratio, the changing ratio of the spring. E.g., 1.1 means the 
	 *	length of the spring will be multiplied with this parameter.	*/
	void addSpringsRestLengthHomogeneous(Real ratio);

	void setFaces(const vector<Vector3f> &tet_faces);

	void setLinearDampingAttributes(float a, float b, float t, float k_max);

	inline void setLoadMeshBoolVariable(bool load_mesh = true);

	//Return how many particles does this system have.
	size_t getParticleCount() const;

	//Return the positions of the particles to the reference.
	void getParticlesPositions(vector< Vector3<Real> > &positions) const;

	//Return how many springs are inside the system.
	size_t getSpringsCount() const;

	//Return the springs info of the system.
	void getSpringsPositions(vector< vector< Vector3<Real> > > &springs_positions) const;

	Vector3f getGravity() const;

	Real getMass() const;

	Real getRestLength() const;

	Real getSpringsStiffness() const;

	Real getBounceEnergyLossRatio() const;

	Real getKineticEnergyLossPerFrame() const;

	Real getKineticEnergyLossIncrease() const;

	Real getKineticEnergyLossThreshold() const;

	bool getLoadMeshBoolVariable();

	void handleLinearDamping(Vector3<Real> &velocity);

	//Update the particle system whenever the timer expires. E.g, updating positions, velocities, etc.
	//The variable dt is the time step which here is specified in seconds.
	void updateParticleSystem(float dt);

	/* 
	*	Collision handling function for the particle with the index.
	*	@extent_ground_y_axis - If the particle's position is below this value, the collistion will be handled.
	*/
	void collisionHandleSimple(Real extent_ground_y_axis, Vector3<Real> &position, Vector3<Real> &velocity);

	//Calculate the reflection of the incoming vector depending on the normal vector.
	Vector3<Real> reflection(Vector3<Real> in, Vector3<Real> normal);

	//Set up the gravity for this particle system. Default value is (0.0f, -9.8f, 0.0f).
	inline void setGravity(Vector3<Real> gravity);

	//Set up the energy loss ratio of the particle system. The default value is 0.95;
	inline void setBounceEnergyLossRatio(float ratio);

	void loadShader(const std::string& vertexShader, const std::string& fragmentShader);
	void constructOnGPU();
	void beginRender();
	void endRender();
	shared_ptr<Shader>& getShader();

public:
	long double rest_length_sum;

	//If it's loading the tetgen meshes or hardcoded meshes.
	bool load_mesh;

	//Linear damping factors.
	//Kd = a * |v| + b
	//a = 0 (when v < thresh), a = a (when v >= thresh)
	//@kd_max, kd cannot be bigger than maximum kd.
	float damping_a;
	float damping_b;
	float v_thresh_for_a;
	float kd_max;

	//Quadratic damping factors.
	float damping_c;
	float v_thresh_for_b;

	//To set if the system is lines shaded or surface shaded.
	bool is_lines_shading;

protected:
	//Called automatically by the setSprings(vector< vector<size_t> > starting_springs) function to initialize the springs' position info.
	inline void _setSpringsPositions();

	//The original faces data were stored as vector<Vector3f>. We want it to be stored in an 1-d array as vector<unsigned int>.
	inline void _converFacesToArray(const vector<Vector3f> &original_faces);

protected:
	size_t particles_count;
	size_t springs_count;
	vector< Particle<Real> > particles;
	vector< Spring<Real> > springs;
	vector<Vector3f> faces;

	Vector3f gravity;
	float bounce_energy_loss_ratio;

	shared_ptr<Shader> shader;
	vector<ParticleVertex> vertices;

	//Used for storing points.
	unsigned int vboId;

	//Used for glDrawElement(GL_LINES, ...), which is basically the springs' connection info.
	vector<unsigned int> eleIndex;

	//Used for glDrawElement(GL_TRIANGLES, ...)
	vector<unsigned int> surIndex;
};


template <class Real>
ParticleSystem<Real>::ParticleSystem(size_t p_count, size_t s_count) : particles_count(p_count), springs_count(s_count) 
{
	initParticleSystem();
}

template <class Real>
ParticleSystem<Real>::~ParticleSystem() 
{
	this->endRender();
}


template <class Real>
void ParticleSystem<Real>::initParticleSystem() {
	//All the values here are default ones.
	this->particles.resize(this->particles_count);
	this->springs.resize(this->springs_count);

	for (size_t i = 0; i < this->particles_count; i++) {
		this->particles[i].position = Vector3f::Zero();
		this->particles[i].velocity = Vector3f::Zero();
		this->particles[i].force = Vector3f::Zero();
		this->particles[i].mass = Real(1);
	}

	for (size_t i = 0; i < this->springs_count; i++) {
		this->springs[i].p0 = Real(0);
		this->springs[i].p1 = Real(0);
		this->springs[i].p0_position = Vector3f::Zero();
		this->springs[i].p1_position = Vector3f::Zero();
		this->springs[i].d_r = Real(25);
		this->springs[i].k = Real(20);
	}

	this->rest_length_sum = 0.0;

	this->load_mesh = true;
	this->gravity = Vector3f(0.0f, -9.8f, 0.0f);
	this->bounce_energy_loss_ratio = 0.95f;

	this->damping_a = 1.0f;
	this->damping_b = 0.0001f;
	this->v_thresh_for_a = 20.0f;
	this->kd_max = 0.65f;

	this->is_lines_shading = true;
}


template <class Real>
void ParticleSystem<Real>::setParticlesPositions(vector< Vector3<Real> > starting_positions) {
	ParticleVertex vert;

	for (size_t i = 0; i < this->particles_count; i++) {
		this->particles[i].position = starting_positions[i];

		vert.position = starting_positions[i];
		vert.color = Color3f(1.0f, 0.5f, 0.5f);
		this->vertices.push_back(vert);
	}
}


template <class Real>
void ParticleSystem<Real>::setParticlesMass(Real mass) {
	for (size_t i = 0; i < this->particles_count; i++) {
		this->particles[i].mass = mass;
	}
}


/* Deprecated for use. It is used for hard coded simple meshes. */
template <class Real>
void ParticleSystem<Real>::setSpringsConnections(vector< vector<size_t> > starting_springs) {
	for (size_t i = 0; i < this->springs_count; i++){
		size_t p0 = starting_springs[i][0];
		size_t p1 = starting_springs[i][1];
		this->springs[i].p0 = p0;
		this->springs[i].p1 = p1;

		//Push them into the array for the shader's processing when using glDrawElement().
		this->eleIndex.push_back(static_cast<unsigned int>(p0)); this->eleIndex.push_back(static_cast<unsigned int>(p1));
	}

	_setSpringsPositions();
}


template <class Real>
void ParticleSystem<Real>::setSpringsConnections(vector<Vector2f> starting_springs) {
	for (size_t i = 0; i < this->springs_count; i++){
		size_t p0 = starting_springs[i].x();
		size_t p1 = starting_springs[i].y();
		this->springs[i].p0 = p0;
		this->springs[i].p1 = p1;

		//Push them into the array for the shader's processing when using glDrawElement().
		this->eleIndex.push_back(static_cast<unsigned int>(p0)); this->eleIndex.push_back(static_cast<unsigned int>(p1));
	}

	_setSpringsPositions();
}


template <class Real>
void ParticleSystem<Real>::setSpringsRestLengthsAsStartingLengths() {
	this->rest_length_sum = 0.0;

	for (size_t i = 0; i < this->springs_count; i++){
		this->springs[i].d_r = Vector3<Real>::Norm(this->springs[i].p0_position - this->springs[i].p1_position);
		this->rest_length_sum += static_cast<long double>(this->springs[i].d_r);
	}
}


template <class Real>
void ParticleSystem<Real>::setSpringsLength(Real length) {
	for (size_t i = 0; i < this->springs_count; i++) {
		this->springs[i].d_r = length;
	}
}


template <class Real>
void ParticleSystem<Real>::setSpringsStiffness(Real k) {
	for (size_t i = 0; i < this->springs_count; i++) {
		this->springs[i].k = k;
	}
}


template <class Real>
void ParticleSystem<Real>::addSpringsRestLength(Real delta) {
	for (size_t i = 0; i < this->springs_count; i++) {
		this->springs[i].d_r += delta;
	}
}


template <class Real>
void ParticleSystem<Real>::addSpringsRestLengthHomogeneous(Real ratio) {
	for (size_t i = 0; i < this->springs_count; i++) {
		if (ratio >= 0)
			this->springs[i].d_r *= (1 + ratio);
		else {
			this->springs[i].d_r /= (1 - ratio);
		}
	}
}


template <class Real>
void ParticleSystem<Real>::setFaces(const vector<Vector3f> &tet_faces) {
	this->faces.resize(tet_faces.size());
	memcpy(&this->faces[0], &tet_faces[0], sizeof(Vector3f) * tet_faces.size());

	this->_converFacesToArray(this->faces);
}


template <class Real>
void ParticleSystem<Real>::setLinearDampingAttributes(float a, float b, float t, float k_max) {
	this->damping_a = a;
	this->damping_b = b;
	this->v_thresh_for_a = t;
	this->kd_max = k_max;
}


template <class Real>
void ParticleSystem<Real>::setLoadMeshBoolVariable(bool load_mesh) {
	this->load_mesh = load_mesh;
}


template <class Real>
size_t ParticleSystem<Real>::getParticleCount() const {
	return this->particles_count;
}


template <class Real>
void ParticleSystem<Real>::getParticlesPositions(vector< Vector3<Real> > &positions) const {
	positions.resize(this->particles_count);

	for (size_t i = 0; i < this->particles_count; i++) {
		positions[i] = this->particles[i].position;
	}
}


template <class Real>
size_t ParticleSystem<Real>::getSpringsCount() const {
	return this->springs_count;
}


template <class Real>
void ParticleSystem<Real>::getSpringsPositions(vector< vector< Vector3<Real> > > &springs_positions) const {
	springs_positions.resize(this->springs_count);
	for (size_t i = 0; i < this->springs_count; i++){
		springs_positions[i].resize(2);

		springs_positions[i][0] = this->springs[i].p0_position;
		springs_positions[i][1] = this->springs[i].p1_position;
	}
}

template <class Real>
Vector3f ParticleSystem<Real>::getGravity() const {
	return this->gravity;
}


template <class Real>
Real ParticleSystem<Real>::getMass() const {
	return this->particles[0].mass;
}


template <class Real>
Real ParticleSystem<Real>::getRestLength() const {
	return this->springs[0].d_r;
}


template <class Real>
Real ParticleSystem<Real>::getSpringsStiffness() const {
	return this->springs[0].k;
}


template <class Real>
Real ParticleSystem<Real>::getBounceEnergyLossRatio() const {
	return this->bounce_energy_loss_ratio;
}


template <class Real>
Real ParticleSystem<Real>::getKineticEnergyLossPerFrame() const {
	return this->energy_loss_per_frame;
}


template <class Real>
Real ParticleSystem<Real>::getKineticEnergyLossIncrease() const {
	return this->energy_loss_per_frame_grow;
}


template <class Real>
Real ParticleSystem<Real>::getKineticEnergyLossThreshold() const {
	return this->energy_loss_per_frame_threshold;
}


template <class Real>
bool ParticleSystem<Real>::getLoadMeshBoolVariable() {
	return this->load_mesh;
}


template <class Real>
void ParticleSystem<Real>::handleLinearDamping(Vector3<Real> &velocity) {
	Vector3<Real> v = velocity;
	float kd = this->damping_b;
	Real speed = Vector3<Real>::Norm(v);
	if (speed > this->v_thresh_for_a)
		kd += this->damping_a * speed;

	if (kd > this->kd_max)
		kd = this->kd_max;

	velocity -= v * kd;
}


template <class Real>
void ParticleSystem<Real>::updateParticleSystem(float dt) {
	for (size_t i = 0; i < this->particles_count; i++) 
		this->particles[i].force = Real(0);

	for (size_t i = 0; i < this->springs_count; i++) {
		//The indices of the current two particles that connect this spring.
		size_t			p0_index	= this->springs[i].p0;
		size_t			p1_index	= this->springs[i].p1;
		Vector3<Real>	p0_pos		= this->particles[p0_index].position;
		Vector3<Real>	p1_pos		= this->particles[p1_index].position;
		float			dr			= this->springs[i].d_r;
		float			k			= this->springs[i].k;

		//vec0 points to the second paricle, which is p1. vec1 points to p0.
		Vector3f vec0 = Vector3<float>::Normalize(p1_pos - p0_pos);
		Vector3f vec1 = Vector3<float>::Normalize(p0_pos - p1_pos);

		//Current distance between these two particles.
		float dc = Vector3<float>::Norm(p1_pos - p0_pos);

		//Calculate the forces influencing these particles.
		this->particles[p0_index].force += k * (dc - dr) * vec0;
		this->particles[p1_index].force += k * (dc - dr) * vec1;
	}

	for (size_t i = 0; i < this->particles_count; i++) {
		this->particles[i].force += this->gravity;

		//The accelaration of the particle.
		Vector3f a = (this->particles[i].force) / (this->particles[i].mass);
		this->particles[i].velocity += a * dt;
		this->handleLinearDamping(this->particles[i].velocity);
		this->collisionHandleSimple(Real(0), this->particles[i].position, this->particles[i].velocity);

		//The updated new positoins of the particles.
		this->particles[i].position += this->particles[i].velocity * dt;
		this->vertices[i].position = this->particles[i].position;
	}

	//Update corresponding two particles' positions in each spring.
	for (size_t i = 0; i < this->springs_count; i++) {
		size_t p_index0 = this->springs[i].p0;
		size_t p_index1 = this->springs[i].p1;
		this->springs[i].p0_position = this->particles[p_index0].position;
		this->springs[i].p1_position = this->particles[p_index1].position;
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertices.size() * sizeof(ParticleVertex), &this->vertices[0]);
}


template <class Real>
void ParticleSystem<Real>::collisionHandleSimple(Real extent_ground_y_axis, Vector3<Real> &position, Vector3<Real> &velocity) {
	if (position.getY() <= extent_ground_y_axis) {
		position.setY( Real(0) );
		velocity *= this->bounce_energy_loss_ratio;

		/* Speed is the norm of the velocity. This block here is to set the direction of the velocity to be upward after a bounce. */
		//Real speed = Vector3<Real>::Norm(velocity);
		//velocity.set( Vector3<Real>( Real(0), speed, Real(0) ) );
		velocity = reflection( velocity, Vector3<Real>( Real(0), Real(1), Real(0) ) );
	}
}


template <class Real>
Vector3<Real> ParticleSystem<Real>::reflection(Vector3<Real> in, Vector3<Real> normal) {
	in = Vector3<Real>() - in;
	Real multiplication = in.x() * normal.x() + in.y() * normal.y() + in.z() * normal.z();
	Real length_in = Vector3<Real>::Norm(in);
	Real length_normal = Vector3<Real>::Norm(normal);
	double phi = acos(multiplication / (length_in * length_normal));

	Vector3<Real> nor_halfsize(normal * length_in * cos(phi));
	Vector3<Real> out(nor_halfsize * 2 - in);
	return out;
}


template <class Real>
inline void ParticleSystem<Real>::setGravity(Vector3<Real> gravity) {
	this->gravity = gravity;
}


template <class Real>
inline void ParticleSystem<Real>::setBounceEnergyLossRatio(float ratio) {
	this->bounce_energy_loss_ratio = ratio;
}


template <class Real>
inline void ParticleSystem<Real>::_setSpringsPositions() {
	for (size_t i = 0; i < this->springs_count; i++){
		this->springs[i].p0_position = this->particles[this->springs[i].p0].position;
		this->springs[i].p1_position = this->particles[this->springs[i].p1].position;
	}
}


template <class Real>
inline void ParticleSystem<Real>::_converFacesToArray(const vector<Vector3f> &original_faces) {
	for (size_t i = 0; i < original_faces.size(); i++) {
		float x = original_faces[i].getX();
		float y = original_faces[i].getY();
		float z = original_faces[i].getZ();

		this->surIndex.push_back(x); this->surIndex.push_back(y); this->surIndex.push_back(z);
	}
}


template <class Real>
void ParticleSystem<Real>::loadShader(const string& vertexShader, const string& fragmentShader) {
	this->shader = make_shared<Shader>();
	this->shader->load(vertexShader, fragmentShader);

	this->shader->compile();
	this->shader->link();
	glBindAttribLocation(this->shader->getProgramID(), POSITION_LOC, "position");
	glBindAttribLocation(this->shader->getProgramID(), COLOR_LOC, "color");
}


template <class Real>
void ParticleSystem<Real>::constructOnGPU() {
	glGenBuffers(1, &this->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(ParticleVertex), &this->vertices[0], GL_DYNAMIC_DRAW);
}


template <class Real>
void ParticleSystem<Real>::beginRender() {
	if (this->shader != nullptr)
		this->shader->enable();

	//Drawing the points' buffer.
	glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
	glEnableVertexAttribArray(POSITION_LOC);
	glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(COLOR_LOC);
	glVertexAttribPointer(COLOR_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), BUFFER_OFFSET(3 * sizeof(float)));

	vector<unsigned int> p_index;
	for (size_t i = 0; i < this->particles_count; i++) {
		p_index.push_back(static_cast<unsigned int>(i));
	}

	glPointSize(5.0f);
	glDrawElements(GL_POINTS, this->particles_count, GL_UNSIGNED_INT, &p_index[0]);

	if (this->is_lines_shading) {
		//glLineWidth(1.0f);
		glDrawElements(GL_LINES, this->eleIndex.size(), GL_UNSIGNED_INT, &this->eleIndex[0]);
	}
	else {
		glDrawElements(GL_TRIANGLES, this->surIndex.size(), GL_UNSIGNED_INT, &this->surIndex[0]);
	}
}


template <class Real>
void ParticleSystem<Real>::endRender() {
	if (this->shader != nullptr)
		this->shader->disable();

	glDisableVertexAttribArray(POSITION_LOC);
	glDisableVertexAttribArray(COLOR_LOC);
	glDeleteBuffers(1, &this->vboId);
}


template <class Real>
shared_ptr<Shader>& ParticleSystem<Real>::getShader() {
	return this->shader;
}