#ifndef MASSSPRINGSYSTEME_H
#define MASSSPRINGSYSTEME_H

#include <QtWidgets/QMainWindow>
#include "ui_massspringsysteme.h"
#include <LoadTetGenFiles.h>
#include <memory>

class MassSpringSysteme : public QMainWindow {
	Q_OBJECT

public:
	MassSpringSysteme(QWidget *parent = 0);
	~MassSpringSysteme();

	void setWidgetsValues();
	void updateHeartCharacteristics();

public:
	shared_ptr<LoadTetGenFiles> tetGenObjs;

public slots:
	/* Function that is called when the "Start" button is released. */
	void slotButtonStart();

	/* Function that is called when the "End" Button is released. */
	void slotButtonEnd();

	/* When the button_line button is clicked. */
	void slotButtonLine();

	/* When the button_Tetrahedron button is clicked. */
	void slotButtonTetrahedron();

	/* When the button_cube button is clicked. */
	void slotButtonCube();

	/* When the button_load button is clicked. */
	void slotButtonLoad();

	/* When the combo_box_load_mesh is activated and the index is changed. */
	void slotComboBoxLoadMeshes();

	void slotPushButtonUpdate();

	void slotPushButtonPumpOnce();

	void slotPushButtonAnimate();

	void slotPushButtonStop();

	void slotRadioButtonRIHo();

	void slotRadioButtonRIHe();

	void slotActionLinesShading();

	void slotActionSurfaceShading();

private:
	Ui::MassSpringSystemeClass ui;
};

#endif // MASSSPRINGSYSTEME_H
