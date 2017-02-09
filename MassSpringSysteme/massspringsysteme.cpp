#include "massspringsysteme.h"

MassSpringSysteme::MassSpringSysteme(QWidget *parent) : QMainWindow(parent) 
{
	ui.setupUi(this);
	this->setWidgetsValues();
}


MassSpringSysteme::~MassSpringSysteme()
{
}


void MassSpringSysteme::setWidgetsValues() {
	Vector3f gravity = ui.glwidget->particleSys->getGravity();
	float mass = ui.glwidget->particleSys->getMass();
	float rc = ui.glwidget->particleSys->getRestLength();
	float ks = ui.glwidget->particleSys->getSpringsStiffness();
	float bel = ui.glwidget->particleSys->getBounceEnergyLossRatio();

	float hi = ui.glwidget->heart_inc;
	float hd = ui.glwidget->heart_dec;
	float hhi = ui.glwidget->heart_homo_inc;
	float hhd = ui.glwidget->heart_homo_dec;
	float hr = ui.glwidget->heart_rate;
	bool is_homo = ui.glwidget->getHomegeneous();

	float a = ui.glwidget->particleSys->damping_a;
	float b = ui.glwidget->particleSys->damping_b;
	float thre_for_a = ui.glwidget->particleSys->v_thresh_for_a;
	float kd_max = ui.glwidget->particleSys->kd_max;

	ui.doubleSpinBox_gravity->setValue((double)gravity.getY());
	ui.doubleSpinBox_mass->setValue((double)mass);
	ui.doubleSpinBox_rc->setValue((double)rc);
	ui.doubleSpinBox_ks->setValue((double)ks);
	ui.doubleSpinBox_bel->setValue((double)bel);

	ui.doubleSpinBox_linearA->setValue((double)a);
	ui.doubleSpinBox_linearB->setValue((double)b);
	ui.doubleSpinBox_linearVt->setValue((double)thre_for_a);
	ui.doubleSpinBox_linearMaxKd->setValue((double)kd_max);

	ui.doubleSpinBox_rld->setValue((double)hi);
	ui.doubleSpinBox_rld_2->setValue((double)hd);
	ui.doubleSpinBox_shi->setValue((double)hhi);
	ui.doubleSpinBox_shd->setValue((double)hhd);
	ui.doubleSpinBox_hr->setValue((double)hr);
	if (is_homo)
		ui.radioButton_ri_ho->setChecked(true);
	else
		ui.radioButton_ri_he->setChecked(true);
}


void MassSpringSysteme::updateHeartCharacteristics() {
	double rest_length_inc = ui.doubleSpinBox_rld->value();
	double rest_length_dec = ui.doubleSpinBox_rld_2->value();
	double hhi = ui.doubleSpinBox_shi->value();
	double hhd = ui.doubleSpinBox_shd->value();
	double heart_rate = ui.doubleSpinBox_hr->value();
	ui.glwidget->setHeartCharacteristics((float)rest_length_inc, (float)rest_length_dec, (float)hhi, (float) hhd, (float)heart_rate);
}


void MassSpringSysteme::slotButtonStart() {
	ui.glwidget->setTimerStart();
}

void MassSpringSysteme::slotButtonEnd() {
	ui.glwidget->setTimerEnd();
}


void MassSpringSysteme::slotButtonLine() {
	ui.glwidget->constructLine();
	ui.glwidget->particleSys->loadShader("shaders/gridShader.vert", "shaders/gridShader.frag");
	ui.glwidget->particleSys->constructOnGPU();

	this->setWidgetsValues();
	ui.glwidget->updateGL();
}


void MassSpringSysteme::slotButtonTetrahedron() {
	ui.glwidget->constructTetrahedron();
	ui.glwidget->particleSys->loadShader("shaders/gridShader.vert", "shaders/gridShader.frag");
	ui.glwidget->particleSys->constructOnGPU();

	this->setWidgetsValues();
	ui.glwidget->updateGL();
}


void MassSpringSysteme::slotButtonCube() {
	ui.glwidget->constructCube();
	ui.glwidget->particleSys->loadShader("shaders/gridShader.vert", "shaders/gridShader.frag");
	ui.glwidget->particleSys->constructOnGPU();

	this->setWidgetsValues();
	ui.glwidget->updateGL();
}


void MassSpringSysteme::slotButtonLoad() {
	int idx = ui.combo_box_load_mesh->currentIndex();

	switch (idx){
	case 0:
		this->tetGenObjs = make_shared<LoadTetGenFiles>("meshes/tube/tube.1.node", 
														"meshes/tube/tube.1.ele", 
														"meshes/tube/tube.1.face");
		break;
	case 1:
		this->tetGenObjs = make_shared<LoadTetGenFiles>("meshes/sphere_simple/sphere_simple.1.node", 
														"meshes/sphere_simple/sphere_simple.1.ele",
														"meshes/sphere_simple/sphere_simple.1.face");
		break;
	case 2:
		this->tetGenObjs = make_shared<LoadTetGenFiles>("meshes/heart_simple/heart_simple.1.node", 
														"meshes/heart_simple/heart_simple.1.ele", 
														"meshes/heart_simple/heart_simple.1.face");
		break;
	case 3:
		this->tetGenObjs = make_shared<LoadTetGenFiles>("meshes/heart_simple/heart_simple_2.1.node", 
														"meshes/heart_simple/heart_simple_2.1.ele", 
														"meshes/heart_simple/heart_simple_2.1.face");
		break;
	case 4:
		this->tetGenObjs = make_shared<LoadTetGenFiles>("meshes/my_heart/my_heart.1.node",
														"meshes/my_heart/my_heart.1.ele",
														"meshes/my_heart/my_heart.1.face");
		break;
	default:
		break;
	}

	ui.glwidget->constructMesh(this->tetGenObjs->particles_num, this->tetGenObjs->springs_num, this->tetGenObjs->starting_positions, this->tetGenObjs->starting_springs, this->tetGenObjs->faces);
	ui.glwidget->particleSys->loadShader("shaders/gridShader.vert", "shaders/gridShader.frag");
	ui.glwidget->particleSys->constructOnGPU();

	this->setWidgetsValues();
	ui.glwidget->updateGL();
}


void MassSpringSysteme::slotComboBoxLoadMeshes() {

}


void MassSpringSysteme::slotPushButtonUpdate() {
	double gravity = ui.doubleSpinBox_gravity->value();
	double mass = ui.doubleSpinBox_mass->value();
	double rc = ui.doubleSpinBox_rc->value();
	double ks = ui.doubleSpinBox_ks->value();
	/* bounce_energy_loss */
	double bel = ui.doubleSpinBox_bel->value();

	float a = static_cast<float>(ui.doubleSpinBox_linearA->value());
	float b = static_cast<float>(ui.doubleSpinBox_linearB->value());
	float t = static_cast<float>(ui.doubleSpinBox_linearVt->value());
	float k_max = static_cast<float>(ui.doubleSpinBox_linearMaxKd->value());

	ui.glwidget->setParticleSystemGeneralAttributes((float)mass, (float)rc, (float)ks, Vector3f(0.0f, (float)gravity, 0.0f));
	ui.glwidget->setParticleSystemEnergyAttributes((float)bel);
	ui.glwidget->particleSys->setLinearDampingAttributes(a, b, t, k_max);
	ui.glwidget->updateGL();
}


void MassSpringSysteme::slotPushButtonPumpOnce() {
	this->updateHeartCharacteristics();
	ui.glwidget->pumpOnce();
}


void MassSpringSysteme::slotPushButtonAnimate() {
	this->updateHeartCharacteristics();
	ui.glwidget->startHeartTimer();
}


void MassSpringSysteme::slotPushButtonStop() {
	ui.glwidget->stopHeartTimer();
}


void MassSpringSysteme::slotRadioButtonRIHo() {
	ui.glwidget->setHomogeneous(true);
}


void MassSpringSysteme::slotRadioButtonRIHe() {
	ui.glwidget->setHomogeneous(false);
}


void MassSpringSysteme::slotActionLinesShading() {
	ui.glwidget->particleSys->is_lines_shading = true;
	ui.glwidget->updateGL();
}


void MassSpringSysteme::slotActionSurfaceShading() {
	bool use_tet_mesh = ui.glwidget->particleSys->getLoadMeshBoolVariable();

	if (use_tet_mesh)
		ui.glwidget->particleSys->is_lines_shading = false;

	ui.glwidget->updateGL();
}