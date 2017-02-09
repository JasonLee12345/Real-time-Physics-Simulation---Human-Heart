/********************************************************************************
** Form generated from reading UI file 'massspringsysteme.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASSSPRINGSYSTEME_H
#define UI_MASSSPRINGSYSTEME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MassSpringSystemeClass
{
public:
    QAction *actionLines_Shading;
    QAction *actionSurface_Shading;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    MyGLWidget *glwidget;
    QFrame *frame;
    QFrame *mesh_frame;
    QPushButton *button_line;
    QPushButton *button_tetrahedron;
    QPushButton *button_cube;
    QLabel *label;
    QComboBox *combo_box_load_mesh;
    QPushButton *button_load;
    QFrame *attr_frame;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_update;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_gravity;
    QDoubleSpinBox *doubleSpinBox_bel;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_rc;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_ks;
    QDoubleSpinBox *doubleSpinBox_mass;
    QLabel *label_2;
    QToolBox *toolBox;
    QWidget *page;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_8;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBox_linearMaxKd;
    QDoubleSpinBox *doubleSpinBox_linearA;
    QDoubleSpinBox *doubleSpinBox_linearB;
    QDoubleSpinBox *doubleSpinBox_linearVt;
    QWidget *page_2;
    QWidget *tab_2;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_rld;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_rld_2;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_hr;
    QPushButton *pushButton_animate;
    QPushButton *pushButton_stop;
    QLabel *label_14;
    QLabel *label_15;
    QDoubleSpinBox *doubleSpinBox_shi;
    QDoubleSpinBox *doubleSpinBox_shd;
    QGroupBox *groupBox;
    QRadioButton *radioButton_ri_he;
    QRadioButton *radioButton_ri_ho;
    QPushButton *pushButton_pumpOnce;
    QWidget *tab_3;
    QFrame *button_frame;
    QPushButton *button_start;
    QPushButton *button_end;
    QMenuBar *menuBar;
    QMenu *menuShading;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MassSpringSystemeClass)
    {
        if (MassSpringSystemeClass->objectName().isEmpty())
            MassSpringSystemeClass->setObjectName(QStringLiteral("MassSpringSystemeClass"));
        MassSpringSystemeClass->resize(1164, 806);
        MassSpringSystemeClass->setStyleSheet(QLatin1String("QMainWindow {\n"
"	background: rgba(50, 50, 50, 200);\n"
"	border: 2px solid gray;\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
"QComboBox {\n"
"     border: 1px solid gray;\n"
"     border-radius: 4px;\n"
"     padding: 1px 18px 1px 3px;\n"
"     min-width: 6em;\n"
" }\n"
"\n"
" QPushButton {\n"
"     background-color:  rgba(220, 220, 220, 200);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 12px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
" QPushButton:pressed {\n"
"     background-color: rgba(255, 255, 255, 250);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 12px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
" QPushButton#pushButton_update {\n"
"     background-color:  rgba(100, 100, 100, 200);\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 5px;\n"
"     border"
                        "-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
"QPushButton#pushButton_pumpOnce {\n"
"     background-color:  rgba(100, 100, 100, 200);\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
"QPushButton#pushButton_animate {\n"
"     background-color:  rgba(100, 100, 100, 200);\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
"QPushButton#pushButton_stop {\n"
"     background-color:  rgba(100, 100, 100, 200);\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
" QPushButton#pushButton_update:presse"
                        "d {\n"
"     background-color:  rgba(240, 240, 240, 200);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
"QPushButton#pushButton_pumpOnce:pressed {\n"
"     background-color:  rgba(240, 240, 240, 200);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
"QPushButton#pushButton_animate:pressed {\n"
"     background-color:  rgba(240, 240, 240, 200);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }\n"
"\n"
"QPushButton#pushButton_stop:pressed {\n"
"     background-color:  rgba(240, 240, 240, 200);\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
""
                        "     border-radius: 5px;\n"
"     border-color: beige;\n"
"     font: bold 14px;\n"
"     min-width: 5em;\n"
"     padding: 2px;\n"
" }"));
        actionLines_Shading = new QAction(MassSpringSystemeClass);
        actionLines_Shading->setObjectName(QStringLiteral("actionLines_Shading"));
        actionSurface_Shading = new QAction(MassSpringSystemeClass);
        actionSurface_Shading->setObjectName(QStringLiteral("actionSurface_Shading"));
        centralWidget = new QWidget(MassSpringSystemeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(1);
        glwidget = new MyGLWidget(splitter);
        glwidget->setObjectName(QStringLiteral("glwidget"));
        splitter->addWidget(glwidget);
        frame = new QFrame(splitter);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(306, 698));
        frame->setMaximumSize(QSize(306, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        mesh_frame = new QFrame(frame);
        mesh_frame->setObjectName(QStringLiteral("mesh_frame"));
        mesh_frame->setGeometry(QRect(10, 10, 286, 152));
        mesh_frame->setMinimumSize(QSize(286, 152));
        mesh_frame->setMaximumSize(QSize(286, 152));
        mesh_frame->setFrameShape(QFrame::StyledPanel);
        mesh_frame->setFrameShadow(QFrame::Raised);
        button_line = new QPushButton(mesh_frame);
        button_line->setObjectName(QStringLiteral("button_line"));
        button_line->setGeometry(QRect(10, 10, 81, 23));
        button_tetrahedron = new QPushButton(mesh_frame);
        button_tetrahedron->setObjectName(QStringLiteral("button_tetrahedron"));
        button_tetrahedron->setGeometry(QRect(100, 10, 91, 23));
        button_cube = new QPushButton(mesh_frame);
        button_cube->setObjectName(QStringLiteral("button_cube"));
        button_cube->setGeometry(QRect(200, 10, 81, 23));
        label = new QLabel(mesh_frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 81, 31));
        label->setStyleSheet(QLatin1String("QLabel \n"
"{ color: rgba(200, 200, 200, 200) }"));
        label->setLineWidth(1);
        combo_box_load_mesh = new QComboBox(mesh_frame);
        combo_box_load_mesh->setObjectName(QStringLiteral("combo_box_load_mesh"));
        combo_box_load_mesh->setGeometry(QRect(10, 70, 251, 31));
        button_load = new QPushButton(mesh_frame);
        button_load->setObjectName(QStringLiteral("button_load"));
        button_load->setGeometry(QRect(130, 110, 131, 31));
        attr_frame = new QFrame(frame);
        attr_frame->setObjectName(QStringLiteral("attr_frame"));
        attr_frame->setGeometry(QRect(10, 170, 286, 511));
        attr_frame->setMinimumSize(QSize(286, 455));
        attr_frame->setFrameShape(QFrame::StyledPanel);
        attr_frame->setFrameShadow(QFrame::Raised);
        tabWidget = new QTabWidget(attr_frame);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(15, 10, 261, 491));
        tabWidget->setStyleSheet(QLatin1String("QTabWidget::pane { /* The tab widget frame */\n"
"    border-top: 2px;\n"
"     border-radius: 4px;\n"
"	background-color: rgba(150, 150, 150, 200);\n"
"}\n"
"\n"
"/*QTabWidget::tab-bar {\n"
"    left: 5px;\n"
"}*/\n"
"\n"
"/*QTabBar::tab {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"    border: 2px;\n"
"    border-bottom-color: rgba(190, 190, 190, 200); \n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    min-width: 5ex;\n"
"    padding: 2px;\n"
"}*/\n"
"\n"
"/*QTabBar::tab:selected {\n"
" 	border: 4px;\n"
"	border-color: rgba(190, 190, 190, 200);\n"
"    border-bottom-color: rgba(190, 190, 190, 200);\n"
"    border-top-left-radius: 5px;\n"
"    border-top-right-radius: 5px;\n"
"    min-width: 5ex;\n"
"    padding: 2px;\n"
"}*/"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_update = new QPushButton(tab);
        pushButton_update->setObjectName(QStringLiteral("pushButton_update"));
        pushButton_update->setGeometry(QRect(120, 430, 141, 31));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 110, 101, 21));
        doubleSpinBox_gravity = new QDoubleSpinBox(tab);
        doubleSpinBox_gravity->setObjectName(QStringLiteral("doubleSpinBox_gravity"));
        doubleSpinBox_gravity->setGeometry(QRect(160, 50, 101, 22));
        doubleSpinBox_gravity->setMinimum(-99.99);
        doubleSpinBox_bel = new QDoubleSpinBox(tab);
        doubleSpinBox_bel->setObjectName(QStringLiteral("doubleSpinBox_bel"));
        doubleSpinBox_bel->setGeometry(QRect(180, 170, 81, 22));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 50, 101, 21));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 80, 81, 21));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 170, 171, 21));
        doubleSpinBox_rc = new QDoubleSpinBox(tab);
        doubleSpinBox_rc->setObjectName(QStringLiteral("doubleSpinBox_rc"));
        doubleSpinBox_rc->setGeometry(QRect(160, 110, 101, 22));
        doubleSpinBox_rc->setMaximum(200);
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 140, 101, 21));
        doubleSpinBox_ks = new QDoubleSpinBox(tab);
        doubleSpinBox_ks->setObjectName(QStringLiteral("doubleSpinBox_ks"));
        doubleSpinBox_ks->setGeometry(QRect(160, 140, 101, 22));
        doubleSpinBox_ks->setMaximum(5000);
        doubleSpinBox_mass = new QDoubleSpinBox(tab);
        doubleSpinBox_mass->setObjectName(QStringLiteral("doubleSpinBox_mass"));
        doubleSpinBox_mass->setGeometry(QRect(160, 80, 101, 22));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 101, 21));
        label_2->setLineWidth(1);
        toolBox = new QToolBox(tab);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(8, 202, 251, 221));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 251, 167));
        label_9 = new QLabel(page);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 40, 71, 21));
        label_10 = new QLabel(page);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 70, 101, 21));
        label_8 = new QLabel(page);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 10, 71, 21));
        label_16 = new QLabel(page);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(20, 100, 71, 16));
        doubleSpinBox_linearMaxKd = new QDoubleSpinBox(page);
        doubleSpinBox_linearMaxKd->setObjectName(QStringLiteral("doubleSpinBox_linearMaxKd"));
        doubleSpinBox_linearMaxKd->setGeometry(QRect(150, 100, 81, 22));
        doubleSpinBox_linearMaxKd->setDecimals(6);
        doubleSpinBox_linearMaxKd->setMaximum(1);
        doubleSpinBox_linearMaxKd->setSingleStep(0.05);
        doubleSpinBox_linearMaxKd->setValue(0.9);
        doubleSpinBox_linearA = new QDoubleSpinBox(page);
        doubleSpinBox_linearA->setObjectName(QStringLiteral("doubleSpinBox_linearA"));
        doubleSpinBox_linearA->setGeometry(QRect(150, 10, 81, 22));
        doubleSpinBox_linearA->setDecimals(6);
        doubleSpinBox_linearA->setSingleStep(0.05);
        doubleSpinBox_linearB = new QDoubleSpinBox(page);
        doubleSpinBox_linearB->setObjectName(QStringLiteral("doubleSpinBox_linearB"));
        doubleSpinBox_linearB->setGeometry(QRect(150, 40, 81, 22));
        doubleSpinBox_linearB->setDecimals(6);
        doubleSpinBox_linearB->setSingleStep(0.005);
        doubleSpinBox_linearVt = new QDoubleSpinBox(page);
        doubleSpinBox_linearVt->setObjectName(QStringLiteral("doubleSpinBox_linearVt"));
        doubleSpinBox_linearVt->setGeometry(QRect(150, 70, 81, 22));
        doubleSpinBox_linearVt->setDecimals(6);
        doubleSpinBox_linearVt->setSingleStep(5);
        toolBox->addItem(page, QStringLiteral("Linear Damping ( Kd = a*|v|+b )"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 100, 30));
        toolBox->addItem(page_2, QStringLiteral("Quadratic Damping"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 60, 161, 21));
        doubleSpinBox_rld = new QDoubleSpinBox(tab_2);
        doubleSpinBox_rld->setObjectName(QStringLiteral("doubleSpinBox_rld"));
        doubleSpinBox_rld->setGeometry(QRect(170, 60, 91, 22));
        doubleSpinBox_rld->setDecimals(4);
        doubleSpinBox_rld->setMinimum(-99.99);
        doubleSpinBox_rld->setSingleStep(0.05);
        doubleSpinBox_rld->setValue(0.5);
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 90, 161, 21));
        doubleSpinBox_rld_2 = new QDoubleSpinBox(tab_2);
        doubleSpinBox_rld_2->setObjectName(QStringLiteral("doubleSpinBox_rld_2"));
        doubleSpinBox_rld_2->setGeometry(QRect(170, 90, 91, 22));
        doubleSpinBox_rld_2->setDecimals(4);
        doubleSpinBox_rld_2->setMinimum(-99.99);
        doubleSpinBox_rld_2->setSingleStep(0.05);
        doubleSpinBox_rld_2->setValue(-0.5);
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 10, 121, 21));
        doubleSpinBox_hr = new QDoubleSpinBox(tab_2);
        doubleSpinBox_hr->setObjectName(QStringLiteral("doubleSpinBox_hr"));
        doubleSpinBox_hr->setGeometry(QRect(170, 10, 91, 22));
        doubleSpinBox_hr->setMinimum(0);
        doubleSpinBox_hr->setMaximum(400);
        doubleSpinBox_hr->setSingleStep(5);
        doubleSpinBox_hr->setValue(60);
        pushButton_animate = new QPushButton(tab_2);
        pushButton_animate->setObjectName(QStringLiteral("pushButton_animate"));
        pushButton_animate->setGeometry(QRect(10, 350, 121, 31));
        pushButton_stop = new QPushButton(tab_2);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(140, 350, 121, 31));
        label_14 = new QLabel(tab_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 140, 161, 16));
        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 170, 161, 16));
        doubleSpinBox_shi = new QDoubleSpinBox(tab_2);
        doubleSpinBox_shi->setObjectName(QStringLiteral("doubleSpinBox_shi"));
        doubleSpinBox_shi->setGeometry(QRect(170, 140, 91, 22));
        doubleSpinBox_shi->setDecimals(6);
        doubleSpinBox_shi->setMinimum(0.01);
        doubleSpinBox_shi->setMaximum(9);
        doubleSpinBox_shi->setSingleStep(0.05);
        doubleSpinBox_shi->setValue(0.01);
        doubleSpinBox_shd = new QDoubleSpinBox(tab_2);
        doubleSpinBox_shd->setObjectName(QStringLiteral("doubleSpinBox_shd"));
        doubleSpinBox_shd->setGeometry(QRect(170, 170, 91, 22));
        doubleSpinBox_shd->setDecimals(6);
        doubleSpinBox_shd->setMinimum(-1);
        doubleSpinBox_shd->setMaximum(0);
        doubleSpinBox_shd->setSingleStep(0.05);
        doubleSpinBox_shd->setValue(-0.01);
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 200, 261, 81));
        radioButton_ri_he = new QRadioButton(groupBox);
        radioButton_ri_he->setObjectName(QStringLiteral("radioButton_ri_he"));
        radioButton_ri_he->setGeometry(QRect(20, 40, 101, 21));
        radioButton_ri_ho = new QRadioButton(groupBox);
        radioButton_ri_ho->setObjectName(QStringLiteral("radioButton_ri_ho"));
        radioButton_ri_ho->setGeometry(QRect(150, 40, 91, 21));
        pushButton_pumpOnce = new QPushButton(tab_2);
        pushButton_pumpOnce->setObjectName(QStringLiteral("pushButton_pumpOnce"));
        pushButton_pumpOnce->setGeometry(QRect(90, 300, 101, 31));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        button_frame = new QFrame(frame);
        button_frame->setObjectName(QStringLiteral("button_frame"));
        button_frame->setGeometry(QRect(10, 680, 286, 71));
        button_frame->setFrameShape(QFrame::StyledPanel);
        button_frame->setFrameShadow(QFrame::Raised);
        button_start = new QPushButton(button_frame);
        button_start->setObjectName(QStringLiteral("button_start"));
        button_start->setGeometry(QRect(20, 10, 111, 41));
        button_start->setMinimumSize(QSize(78, 0));
        button_end = new QPushButton(button_frame);
        button_end->setObjectName(QStringLiteral("button_end"));
        button_end->setGeometry(QRect(150, 10, 111, 41));
        splitter->addWidget(frame);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MassSpringSystemeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MassSpringSystemeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1164, 21));
        menuShading = new QMenu(menuBar);
        menuShading->setObjectName(QStringLiteral("menuShading"));
        MassSpringSystemeClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MassSpringSystemeClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MassSpringSystemeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MassSpringSystemeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MassSpringSystemeClass->setStatusBar(statusBar);

        menuBar->addAction(menuShading->menuAction());
        menuShading->addAction(actionLines_Shading);
        menuShading->addAction(actionSurface_Shading);

        retranslateUi(MassSpringSystemeClass);
        QObject::connect(button_start, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotButtonStart()));
        QObject::connect(button_line, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotButtonLine()));
        QObject::connect(button_end, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotButtonEnd()));
        QObject::connect(button_tetrahedron, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotButtonTetrahedron()));
        QObject::connect(button_cube, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotButtonCube()));
        QObject::connect(button_load, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotButtonLoad()));
        QObject::connect(combo_box_load_mesh, SIGNAL(currentIndexChanged(int)), MassSpringSystemeClass, SLOT(slotComboBoxLoadMeshes()));
        QObject::connect(pushButton_update, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotPushButtonUpdate()));
        QObject::connect(pushButton_animate, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotPushButtonAnimate()));
        QObject::connect(pushButton_stop, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotPushButtonStop()));
        QObject::connect(radioButton_ri_ho, SIGNAL(pressed()), MassSpringSystemeClass, SLOT(slotRadioButtonRIHo()));
        QObject::connect(radioButton_ri_he, SIGNAL(pressed()), MassSpringSystemeClass, SLOT(slotRadioButtonRIHe()));
        QObject::connect(pushButton_pumpOnce, SIGNAL(released()), MassSpringSystemeClass, SLOT(slotPushButtonPumpOnce()));
        QObject::connect(actionLines_Shading, SIGNAL(triggered()), MassSpringSystemeClass, SLOT(slotActionLinesShading()));
        QObject::connect(actionSurface_Shading, SIGNAL(triggered()), MassSpringSystemeClass, SLOT(slotActionSurfaceShading()));

        tabWidget->setCurrentIndex(1);
        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MassSpringSystemeClass);
    } // setupUi

    void retranslateUi(QMainWindow *MassSpringSystemeClass)
    {
        MassSpringSystemeClass->setWindowTitle(QApplication::translate("MassSpringSystemeClass", "MassSpringSysteme", 0));
        actionLines_Shading->setText(QApplication::translate("MassSpringSystemeClass", "Lines Shading", 0));
        actionSurface_Shading->setText(QApplication::translate("MassSpringSystemeClass", "Surface Shading", 0));
        button_line->setText(QApplication::translate("MassSpringSystemeClass", "Line", 0));
        button_tetrahedron->setText(QApplication::translate("MassSpringSystemeClass", "Tetrahedron", 0));
        button_cube->setText(QApplication::translate("MassSpringSystemeClass", "Cube", 0));
        label->setText(QApplication::translate("MassSpringSystemeClass", "Load Meshes:", 0));
        combo_box_load_mesh->clear();
        combo_box_load_mesh->insertItems(0, QStringList()
         << QApplication::translate("MassSpringSystemeClass", "Tube", 0)
         << QApplication::translate("MassSpringSystemeClass", "Sphere", 0)
         << QApplication::translate("MassSpringSystemeClass", "Simple Heart", 0)
         << QApplication::translate("MassSpringSystemeClass", "Complex Heart", 0)
         << QApplication::translate("MassSpringSystemeClass", "Real Heart", 0)
        );
        button_load->setText(QApplication::translate("MassSpringSystemeClass", "Load", 0));
        pushButton_update->setText(QApplication::translate("MassSpringSystemeClass", "Update", 0));
        label_4->setText(QApplication::translate("MassSpringSystemeClass", "Spring Rest Length:", 0));
        label_6->setText(QApplication::translate("MassSpringSystemeClass", "System Gravity:", 0));
        label_3->setText(QApplication::translate("MassSpringSystemeClass", "Particle Mass:", 0));
        label_7->setText(QApplication::translate("MassSpringSystemeClass", "Bounce Energy Loss (per bounce):", 0));
        label_5->setText(QApplication::translate("MassSpringSystemeClass", "Spring Stiffness:", 0));
        label_2->setText(QApplication::translate("MassSpringSystemeClass", "System Attributes:", 0));
        label_9->setText(QApplication::translate("MassSpringSystemeClass", "b:", 0));
        label_10->setText(QApplication::translate("MassSpringSystemeClass", "|Vt|:", 0));
        label_8->setText(QApplication::translate("MassSpringSystemeClass", "a:", 0));
        label_16->setText(QApplication::translate("MassSpringSystemeClass", "Maximum Kd:", 0));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MassSpringSystemeClass", "Linear Damping ( Kd = a*|v|+b )", 0));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MassSpringSystemeClass", "Quadratic Damping", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MassSpringSystemeClass", "General", 0));
        label_11->setText(QApplication::translate("MassSpringSystemeClass", "Spring Heterogeneous Increase:", 0));
        label_12->setText(QApplication::translate("MassSpringSystemeClass", "Spring Heterogeneous Decrease:", 0));
        label_13->setText(QApplication::translate("MassSpringSystemeClass", "Heart Rate (bpm):", 0));
        pushButton_animate->setText(QApplication::translate("MassSpringSystemeClass", "Animate", 0));
        pushButton_stop->setText(QApplication::translate("MassSpringSystemeClass", "Stop", 0));
        label_14->setText(QApplication::translate("MassSpringSystemeClass", "Spring Homogeneous Increase:", 0));
        label_15->setText(QApplication::translate("MassSpringSystemeClass", "Spring Homogeneous Decrease:", 0));
        groupBox->setTitle(QApplication::translate("MassSpringSystemeClass", "Method:", 0));
        radioButton_ri_he->setText(QApplication::translate("MassSpringSystemeClass", "Heterogeneous", 0));
        radioButton_ri_ho->setText(QApplication::translate("MassSpringSystemeClass", "Homogeneous", 0));
        pushButton_pumpOnce->setText(QApplication::translate("MassSpringSystemeClass", "Pump Once", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MassSpringSystemeClass", "RI", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MassSpringSystemeClass", "SI", 0));
        button_start->setText(QApplication::translate("MassSpringSystemeClass", "Start", 0));
        button_end->setText(QApplication::translate("MassSpringSystemeClass", "End", 0));
        menuShading->setTitle(QApplication::translate("MassSpringSystemeClass", "Shading", 0));
    } // retranslateUi

};

namespace Ui {
    class MassSpringSystemeClass: public Ui_MassSpringSystemeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASSSPRINGSYSTEME_H
