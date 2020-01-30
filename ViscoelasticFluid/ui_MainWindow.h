/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSplitter *splitter_2;
    QGridLayout *s_mainWindowGridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *m_generate;
    QPushButton *m_reset;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *m_particles;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *m_spread;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QCheckBox *m_velocity;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QCheckBox *m_springs;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QCheckBox *m_relaxation;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QDoubleSpinBox *m_plasticity;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QDoubleSpinBox *m_elasticity;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QDoubleSpinBox *m_pressure;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QCheckBox *m_viscosity;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QDoubleSpinBox *m_fluidity;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QDoubleSpinBox *m_gravity;
    QDoubleSpinBox *m_ir;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QDoubleSpinBox *m_density;
    QSplitter *splitter;
    QLabel *label_14;
    QLabel *label_15;
    QMenuBar *menubar;
    QMenu *menuViscoelastid_Fluid_Simulation;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(859, 687);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(0, 0, 100, 30));
        splitter_2->setOrientation(Qt::Horizontal);
        s_mainWindowGridLayout = new QGridLayout(centralwidget);
        s_mainWindowGridLayout->setObjectName(QString::fromUtf8("s_mainWindowGridLayout"));
        s_mainWindowGridLayout->setContentsMargins(9, 9, -1, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        s_mainWindowGridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        m_generate = new QPushButton(centralwidget);
        m_generate->setObjectName(QString::fromUtf8("m_generate"));

        horizontalLayout_13->addWidget(m_generate);

        m_reset = new QPushButton(centralwidget);
        m_reset->setObjectName(QString::fromUtf8("m_reset"));

        horizontalLayout_13->addWidget(m_reset);


        s_mainWindowGridLayout->addLayout(horizontalLayout_13, 2, 2, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 161, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_particles = new QSpinBox(layoutWidget);
        m_particles->setObjectName(QString::fromUtf8("m_particles"));
        m_particles->setMinimum(0);
        m_particles->setMaximum(2000);
        m_particles->setValue(0);

        horizontalLayout->addWidget(m_particles);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 70, 161, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        m_spread = new QDoubleSpinBox(layoutWidget1);
        m_spread->setObjectName(QString::fromUtf8("m_spread"));
        m_spread->setMaximum(1.000000000000000);
        m_spread->setSingleStep(0.010000000000000);
        m_spread->setValue(0.000000000000000);

        horizontalLayout_2->addWidget(m_spread);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(11, 120, 161, 31));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        m_velocity = new QCheckBox(layoutWidget2);
        m_velocity->setObjectName(QString::fromUtf8("m_velocity"));
        m_velocity->setChecked(true);

        horizontalLayout_3->addWidget(m_velocity);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 160, 161, 391));
        layoutWidget3 = new QWidget(groupBox_2);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 100, 101, 31));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        m_springs = new QCheckBox(layoutWidget3);
        m_springs->setObjectName(QString::fromUtf8("m_springs"));
        m_springs->setChecked(true);
        m_springs->setTristate(false);

        horizontalLayout_5->addWidget(m_springs);

        layoutWidget_2 = new QWidget(groupBox_2);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 200, 121, 45));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        m_relaxation = new QCheckBox(layoutWidget_2);
        m_relaxation->setObjectName(QString::fromUtf8("m_relaxation"));
        m_relaxation->setEnabled(true);
        m_relaxation->setAcceptDrops(false);
        m_relaxation->setChecked(true);
        m_relaxation->setTristate(false);

        horizontalLayout_6->addWidget(m_relaxation);

        layoutWidget_3 = new QWidget(groupBox_2);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 130, 137, 31));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_8->addWidget(label_8);

        m_plasticity = new QDoubleSpinBox(layoutWidget_3);
        m_plasticity->setObjectName(QString::fromUtf8("m_plasticity"));
        m_plasticity->setMaximum(1.000000000000000);
        m_plasticity->setSingleStep(0.010000000000000);
        m_plasticity->setValue(0.300000000000000);

        horizontalLayout_8->addWidget(m_plasticity);

        layoutWidget_4 = new QWidget(groupBox_2);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 160, 137, 31));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_9->addWidget(label_9);

        m_elasticity = new QDoubleSpinBox(layoutWidget_4);
        m_elasticity->setObjectName(QString::fromUtf8("m_elasticity"));
        m_elasticity->setMaximum(1.000000000000000);
        m_elasticity->setSingleStep(0.010000000000000);
        m_elasticity->setValue(0.300000000000000);

        horizontalLayout_9->addWidget(m_elasticity);

        layoutWidget_5 = new QWidget(groupBox_2);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 240, 135, 31));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_10->addWidget(label_10);

        m_pressure = new QDoubleSpinBox(layoutWidget_5);
        m_pressure->setObjectName(QString::fromUtf8("m_pressure"));
        m_pressure->setMaximum(1.000000000000000);
        m_pressure->setSingleStep(0.010000000000000);
        m_pressure->setValue(0.100000000000000);

        horizontalLayout_10->addWidget(m_pressure);

        layoutWidget4 = new QWidget(groupBox_2);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 30, 101, 31));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        m_viscosity = new QCheckBox(layoutWidget4);
        m_viscosity->setObjectName(QString::fromUtf8("m_viscosity"));
        m_viscosity->setChecked(true);
        m_viscosity->setTristate(false);

        horizontalLayout_4->addWidget(m_viscosity);

        layoutWidget5 = new QWidget(groupBox_2);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(10, 60, 127, 31));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        m_fluidity = new QDoubleSpinBox(layoutWidget5);
        m_fluidity->setObjectName(QString::fromUtf8("m_fluidity"));
        m_fluidity->setMaximum(1.000000000000000);
        m_fluidity->setSingleStep(0.010000000000000);
        m_fluidity->setValue(0.300000000000000);

        horizontalLayout_7->addWidget(m_fluidity);

        layoutWidget6 = new QWidget(groupBox_2);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(10, 360, 141, 31));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget6);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_12->addWidget(label_12);

        m_gravity = new QDoubleSpinBox(layoutWidget6);
        m_gravity->setObjectName(QString::fromUtf8("m_gravity"));
        m_gravity->setMaximum(1.000000000000000);
        m_gravity->setSingleStep(0.010000000000000);
        m_gravity->setValue(0.000000000000000);

        horizontalLayout_12->addWidget(m_gravity);

        m_ir = new QDoubleSpinBox(groupBox_2);
        m_ir->setObjectName(QString::fromUtf8("m_ir"));
        m_ir->setGeometry(QRect(90, 308, 61, 41));
        m_ir->setDecimals(2);
        m_ir->setMaximum(1.000000000000000);
        m_ir->setSingleStep(0.010000000000000);
        m_ir->setValue(0.200000000000000);
        layoutWidget_6 = new QWidget(groupBox_2);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 270, 141, 31));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_11->addWidget(label_11);

        m_density = new QDoubleSpinBox(layoutWidget_6);
        m_density->setObjectName(QString::fromUtf8("m_density"));
        m_density->setMinimum(1.000000000000000);
        m_density->setMaximum(10.000000000000000);
        m_density->setSingleStep(0.100000000000000);
        m_density->setValue(4.000000000000000);

        horizontalLayout_11->addWidget(m_density);

        splitter = new QSplitter(groupBox_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(10, 310, 71, 40));
        splitter->setOrientation(Qt::Vertical);
        label_14 = new QLabel(splitter);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        splitter->addWidget(label_14);
        label_15 = new QLabel(splitter);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        splitter->addWidget(label_15);

        s_mainWindowGridLayout->addWidget(groupBox, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 859, 25));
        menuViscoelastid_Fluid_Simulation = new QMenu(menubar);
        menuViscoelastid_Fluid_Simulation->setObjectName(QString::fromUtf8("menuViscoelastid_Fluid_Simulation"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuViscoelastid_Fluid_Simulation->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        m_generate->setText(QApplication::translate("MainWindow", "Generate", nullptr));
        m_reset->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Generation Parameters", nullptr));
        label->setText(QApplication::translate("MainWindow", "Number", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Spread", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Rand Initial Velocity", nullptr));
        m_velocity->setText(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Characterisitics", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Springs", nullptr));
        m_springs->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Relaxation", nullptr));
        m_relaxation->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "Plasticity", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Elasticity", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Pressure", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Viscosity ", nullptr));
        m_viscosity->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "Fluidity", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Gravity", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Density", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "Interaction", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "Radius", nullptr));
        menuViscoelastid_Fluid_Simulation->setTitle(QApplication::translate("MainWindow", "Viscoelastid Fluid Simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
