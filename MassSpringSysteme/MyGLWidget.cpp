#include "MyGLWidget.h"
#include <iostream>
#include <LoadTetGenFiles.h>


MyGLWidget::MyGLWidget(QWidget *parent) : 
QGLWidget(parent)
{
	this->setMouseTracking(true);
	this->setFocusPolicy(Qt::StrongFocus);
	this->setFocus();
	this->camera = make_shared<MouseCameraf>();

	/* Initialize the meshes. */
	this->grid = make_shared<Grid>();
	this->constructCube();

	//Set the fps to be 62. Because 1000 / 16 = 62.
	this->timeStep = 0.016f;
	this->timer = new QTimer(this);
	this->connect(this->timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
	this->timer->setInterval(16);

	this->heart_beated = false;
	this->is_homogeneous = true;

	this->heart_inc = 0.5f;
	this->heart_dec = -0.5f;
	this->heart_homo_inc = 0.079605f;
	this->heart_homo_dec = -0.079605f;
	this->heart_rate = 60;
	this->beats_count = 0;
	this->pump_once = false;

	this->heart_rate_timer = new QTimer(this);
	this->connect(this->heart_rate_timer, SIGNAL(timeout()), this, SLOT(heartBeat()));
	this->heart_rate_timer->setInterval((float)60 / this->heart_rate * (float)500);
}


MyGLWidget::~MyGLWidget()
{
	this->grid->endRender();
}


void MyGLWidget::initializeGL() {
	initializeGLFunctions();
	color_background = QColor::fromCmykF(0.35, 0.36, 0.36, 0.0);
	qglClearColor(color_background.dark());

	glewInit();

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->camera->setPosition(90.0f, 1.570f, 1.570f * 0.7f);
	this->camera->setLookAt(Vector3f(0.0f, 10.0f, 0.0f));

	this->grid->loadShader("shaders/gridShader.vert", "shaders/gridShader.frag");
	this->grid->constructGrid(Color3f(0.0f, 0.3f, 0.3f), -10.0f, -100.0f, 100.0f, -100.0f, 100.0f);

	this->particleSys->loadShader("shaders/gridShader.vert", "shaders/gridShader.frag");
	this->particleSys->constructOnGPU();
}


void MyGLWidget::paintGL() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->modelViewMatrix = this->camera->getViewMatrix();
	this->projectionMatrix = this->camera->getProjectionMatrix();
	this->mvp = this->projectionMatrix * this->modelViewMatrix;

	/* Draw the ground. */
	this->grid->beginRender();
	this->grid->getShader()->uniformMatrix("modelViewMatrix", modelViewMatrix);
	this->grid->getShader()->uniformMatrix("projectionMatrix", projectionMatrix);

	this->particleSys->beginRender();
	this->particleSys->getShader()->uniformMatrix("modelViewMatrix", modelViewMatrix);
	this->particleSys->getShader()->uniformMatrix("projectionMatrix", projectionMatrix);
}


void MyGLWidget::resizeGL(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	//gluPerspective(65.0, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
	this->camera->setPerspective(65.0f, (GLfloat)width / (GLfloat)height, 0.5f, 1000.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float proj[16];
	this->camera->getProjectionMatrix().toRawMatrix(proj);
	glMultMatrixf(proj);
	glMatrixMode(GL_MODELVIEW);
}


void MyGLWidget::setTimerStart() {
	this->timer->start();
}


void MyGLWidget::setTimerEnd() {
	this->timer->stop();
}


inline void MyGLWidget::setParticleSystemGeneralAttributes(float particle_mass, float spring_rest_length, float spring_stiffness, Vector3f gravity) {
	this->particleSys->setParticlesMass(particle_mass);

	/*	If we are loading the hard coded meshes, the rc can be changed randomly.
	 *	But when the tetgen files are loaded, the rc should always be the inital ones.  */
	if (!this->particleSys->load_mesh)
		this->particleSys->setSpringsLength(spring_rest_length);

	this->particleSys->setSpringsStiffness(spring_stiffness);
	this->particleSys->setGravity(gravity);
}


void MyGLWidget::setParticleSystemEnergyAttributes(float bounce_energy_loss_ratio) {
	this->particleSys->setBounceEnergyLossRatio(bounce_energy_loss_ratio);
}


void MyGLWidget::setHomogeneous(bool is_homo) {
	this->is_homogeneous = is_homo;
}


bool MyGLWidget::getHomegeneous() const {
	return this->is_homogeneous;
}


void MyGLWidget::constructLine() {
	/* Initialize the starting positions of the particles. */
	size_t particles_num = 2;
	this->starting_positions.resize(particles_num);
	this->starting_positions[0] = Vector3f(-15.0f, 15.0f, 0.0f);
	this->starting_positions[1] = Vector3f(15.0f, 10.0f, 0.0f);

	/* Initialize the info of the connections of the springs. */
	size_t springs_num = 1;
	this->starting_springs.resize(springs_num);
	for (size_t i = 0; i < springs_num; i++){
		this->starting_springs[i].resize(2);
	}

	this->starting_springs[0][0] = (size_t)0;
	this->starting_springs[0][1] = (size_t)1;

	/* Initialize the particle system with particles and springs set up. */
	this->particleSys = make_shared< ParticleSystem<float> >(particles_num, springs_num);
	this->particleSys->setParticlesPositions(this->starting_positions);
	this->particleSys->setSpringsConnections(this->starting_springs);

	this->particleSys->setLoadMeshBoolVariable(false);
	this->setParticleSystemGeneralAttributes(2.0f, 28.0f, 4.0f, Vector3f(0.0f, -6.0f, 0.0f));
	this->setParticleSystemEnergyAttributes(0.9f);
}


void MyGLWidget::constructTetrahedron() {
	/* Initialize the starting positions of the particles. */
	size_t particles_num = 4;
	this->starting_positions.resize(particles_num);
	this->starting_positions[0] = Vector3f(-20.0f, 10.0f, 0.0f);
	this->starting_positions[1] = Vector3f(20.0f, 10.0f, 0.0f);
	this->starting_positions[2] = Vector3f(0.0f, 10.0f, -34.64f);
	this->starting_positions[3] = Vector3f(0.0f, 42.66f, -11.55f);

	/* Initialize the info of the connections of the springs. */
	size_t springs_num = 6;
	this->starting_springs.resize(springs_num);
	for (size_t i = 0; i < springs_num; i++){
		this->starting_springs[i].resize(2);
	}

	this->starting_springs[0][0] = (size_t)0;
	this->starting_springs[0][1] = (size_t)1;

	this->starting_springs[1][0] = (size_t)1;
	this->starting_springs[1][1] = (size_t)2;

	this->starting_springs[2][0] = (size_t)0;
	this->starting_springs[2][1] = (size_t)2;

	this->starting_springs[3][0] = (size_t)0;
	this->starting_springs[3][1] = (size_t)3;

	this->starting_springs[4][0] = (size_t)1;
	this->starting_springs[4][1] = (size_t)3;

	this->starting_springs[5][0] = (size_t)2;
	this->starting_springs[5][1] = (size_t)3;

	/* Initialize the particle system with particles and springs set up. */
	this->particleSys = make_shared< ParticleSystem<float> >(particles_num, springs_num);
	this->particleSys->setParticlesPositions(this->starting_positions);
	this->particleSys->setSpringsConnections(this->starting_springs);

	this->particleSys->setLoadMeshBoolVariable(false);
	this->setParticleSystemGeneralAttributes(2.0f, 39.5f, 4.0f, Vector3f(0.0f, -6.0f, 0.0f));
	this->setParticleSystemEnergyAttributes(0.9f);
}


void MyGLWidget::constructCube() {
	/* Initialize the starting positions of the particles. */
	size_t particles_num = 8;
	this->starting_positions.resize(particles_num);

	this->starting_positions[0] = Vector3f(-10.0f, 10.0f, 10.0f);
	this->starting_positions[1] = Vector3f(10.0f, 10.0f, 10.0f);
	this->starting_positions[2] = Vector3f(10.0f, 10.0f, -10.0f);
	this->starting_positions[3] = Vector3f(-10.0f, 10.0f, -10.0f);
	this->starting_positions[4] = Vector3f(-10.0f, 30.0f, 10.0f);
	this->starting_positions[5] = Vector3f(10.0f, 30.0f, 10.0f);
	this->starting_positions[6] = Vector3f(10.0f, 30.0f, -10.0f);
	this->starting_positions[7] = Vector3f(-10.0f, 30.0f, -10.0f);

	/* Initialize the info of the connections of the springs. */
	size_t springs_num = 12;
	this->starting_springs.resize(springs_num);
	for (size_t i = 0; i < springs_num; i++){
		this->starting_springs[i].resize(2);
	}

	this->starting_springs[0][0] = (size_t)0;
	this->starting_springs[0][1] = (size_t)1;

	this->starting_springs[1][0] = (size_t)1;
	this->starting_springs[1][1] = (size_t)2;

	this->starting_springs[2][0] = (size_t)2;
	this->starting_springs[2][1] = (size_t)3;

	this->starting_springs[3][0] = (size_t)0;
	this->starting_springs[3][1] = (size_t)3;

	this->starting_springs[4][0] = (size_t)0;
	this->starting_springs[4][1] = (size_t)4;

	this->starting_springs[5][0] = (size_t)1;
	this->starting_springs[5][1] = (size_t)5;

	this->starting_springs[6][0] = (size_t)2;
	this->starting_springs[6][1] = (size_t)6;

	this->starting_springs[7][0] = (size_t)3;
	this->starting_springs[7][1] = (size_t)7;

	this->starting_springs[8][0] = (size_t)4;
	this->starting_springs[8][1] = (size_t)5;

	this->starting_springs[9][0] = (size_t)5;
	this->starting_springs[9][1] = (size_t)6;

	this->starting_springs[10][0] = (size_t)7;
	this->starting_springs[10][1] = (size_t)6;

	this->starting_springs[11][0] = (size_t)4;
	this->starting_springs[11][1] = (size_t)7;

	/* Initialize the particle system with particles and springs set up. */
	this->particleSys = make_shared< ParticleSystem<float> >(particles_num, springs_num);
	this->particleSys->setParticlesPositions(this->starting_positions);
	this->particleSys->setSpringsConnections(this->starting_springs);

	this->particleSys->setLoadMeshBoolVariable(false);
	this->setParticleSystemGeneralAttributes(2.0f, 19.5f, 20.0f, Vector3f(0.0f, -6.0f, 0.0f));
	this->setParticleSystemEnergyAttributes(0.9f);
}


void MyGLWidget::constructMesh(size_t particles_num, size_t springs_num, vector<Vector3f> starting_positions, vector<Vector2f> starting_springs, vector<Vector3f> faces) {
	this->particleSys = make_shared< ParticleSystem<float> >(particles_num, springs_num);
	this->particleSys->setParticlesPositions(starting_positions);
	this->particleSys->setSpringsConnections(starting_springs);
	this->particleSys->setFaces(faces);
	this->particleSys->setSpringsRestLengthsAsStartingLengths();

	this->particleSys->setLoadMeshBoolVariable(true);
	this->particleSys->setParticlesMass(2.5f);
	this->particleSys->setSpringsStiffness(180.0f);
	this->particleSys->setGravity(Vector3f(0.0f, 0.0f, 0.0f));
	this->setParticleSystemEnergyAttributes(0.9f);
	std::cout << "Springs' average rest length is: " << this->printSpringsAverageRestLength() << endl;
}


long double MyGLWidget::printSpringsAverageRestLength() {
	long double springs_num = static_cast<long double>(this->particleSys->getSpringsCount());
	long double average = this->particleSys->rest_length_sum / springs_num;
	return average;
}


void MyGLWidget::setHeartCharacteristics(float inc, float dec, float hi, float hd, float hr) {
	this->heart_inc = inc;
	this->heart_dec = dec;
	this->heart_homo_inc = hi;
	this->heart_homo_dec = hd;
	this->heart_rate = hr;
}


void MyGLWidget::startHeartTimer() {
	this->heart_rate_timer->setInterval((float)60 / this->heart_rate * (float)500);
	this->heart_rate_timer->start();
}


void MyGLWidget::stopHeartTimer() {
	this->heart_rate_timer->stop();
	this->beats_count = 0;
	this->pump_once = false;
	this->heart_beated = false;
}


void MyGLWidget::pumpOnce() {
	this->pump_once = true;
	this->startHeartTimer();
}


void MyGLWidget::heartBeat() {
	if (!this->heart_beated) {
		if (is_homogeneous)
			this->particleSys->addSpringsRestLengthHomogeneous(this->heart_homo_dec);
		else
			this->particleSys->addSpringsRestLength(this->heart_dec);
	}
	else {
		if (is_homogeneous)
			this->particleSys->addSpringsRestLengthHomogeneous(this->heart_homo_inc);
		else
			this->particleSys->addSpringsRestLength(this->heart_inc);
	}
	
	heart_beated = !heart_beated;
	this->beats_count++;

	if (this->pump_once)
		if (this->beats_count == 2)
			this->stopHeartTimer();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent* e) {
	this->camera->onMouseMove(e->x(), e->y());
	this->updateGL();
}


void MyGLWidget::mousePressEvent(QMouseEvent* e) {
	if (e->button() == Qt::LeftButton)
		this->camera->onMouseButton(LB_DOWN, e->x(), e->y());
	
	if (e->button() == Qt::RightButton)
		this->camera->onMouseButton(RB_DOWN, e->x(), e->y());

	this->updateGL();
}


void MyGLWidget::mouseReleaseEvent(QMouseEvent* e) {
	if (e->button() == Qt::LeftButton)
		this->camera->onMouseButton(LB_UP, e->x(), e->y());
	
	if (e->button() == Qt::RightButton)
		this->camera->onMouseButton(RB_UP, e->x(), e->y());

	this->updateGL();
}


void MyGLWidget::keyPressEvent(QKeyEvent* e) {
	switch ( e->key() ) {
	case Qt::Key_Up:
		this->camera->onKey(KEY_UP);
		break;
	case Qt::Key_Down:
		this->camera->onKey(KEY_DOWN);
		break;
	case Qt::Key_Left:
		this->camera->onKey(KEY_LEFT);
		break;
	case Qt::Key_Right:
		this->camera->onKey(KEY_RIGHT);
		break;
	default:
		break;
	}

	this->updateGL();
}


void MyGLWidget::slotTimeout() {
	this->particleSys->updateParticleSystem(this->timeStep);
	this->updateGL();
}