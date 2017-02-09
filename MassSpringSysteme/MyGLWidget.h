#pragma once

#include <gl/glew.h>
#include "ParticleSystem.h"
#include <MouseCamera.h>
#include <Matrix4.h>
#include <QGLWidget>
#include <QtOpenGL>
#include <memory>
#include <Grid.h>

class MyGLWidget : public QGLWidget, protected QGLFunctions {
	Q_OBJECT

public:
	MyGLWidget(QWidget *parent = 0);
	~MyGLWidget();

	void setTimerStart();
	void setTimerEnd();
	inline void setParticleSystemGeneralAttributes(float particle_mass, float spring_rest_length, float spring_stiffness, Vector3f gravity);
	void setParticleSystemEnergyAttributes(float bounce_energy_loss_ratio);
	void setHomogeneous(bool is_homo);
	bool getHomegeneous() const;

	//The integrated meshed that are already in the program.
	void constructLine();
	void constructTetrahedron();
	void constructCube();

	//This function will load a mesh into the program and will be handled by this interface.
	void constructMesh(size_t particle_num, size_t springs_num, vector<Vector3f> starting_positions, vector<Vector2f> starting_springs, vector<Vector3f> faces);
	long double printSpringsAverageRestLength();

	/*	@inc, the increasement of the springs' rest length.
	*	@dec, the decreasement of the springs' rest length.
	*	@homo_inc, the homogeneous increasement for springs.	*/
	void setHeartCharacteristics(float inc, float dec, float homo_inc, float homo_dec, float heart_rate);
	void startHeartTimer();
	void stopHeartTimer();
	void pumpOnce();

	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);

public slots:
	void slotTimeout();
	void heartBeat();

public:
	shared_ptr< ParticleSystem<float> > particleSys;

	//Line's info. The starting attributes of the particles. The info about the springs. Basically, this tells which particles are connected.
	vector<Vector3f> starting_positions;
	vector< vector<size_t> > starting_springs;

	const static float camCenter[3];
	const static float camLookAt[3];
	float camCenterDelta[3];
	float camLookAtDelta[3];

	//Parameters for heartbeat.
	float heart_inc;
	float heart_dec;
	float heart_homo_inc;
	float heart_homo_dec;
	float heart_rate;

	// Either a systole or a diastol is counted as a beat.
	size_t beats_count;
	bool pump_once;

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

protected:
	shared_ptr<Grid> grid;
	shared_ptr<MouseCameraf> camera;
	Matrix4f modelViewMatrix;
	Matrix4f projectionMatrix;
	Matrix4f mvp;

	QColor color_background;
	QTimer *timer;
	float timeStep;

	QTimer *heart_rate_timer;
	float heart_beated;

	//If it is false, it means using heterogeneous method.
	bool is_homogeneous;
};