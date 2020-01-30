#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_gl=new  NGLScene(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,2);


//  set the generation parameters
   connect(m_ui->m_particles,SIGNAL(valueChanged(int)),this,SLOT(setParticleNumber(int)));
   connect(m_ui->m_spread,SIGNAL(valueChanged(double)),this,SLOT(setSpread(double)));
   connect(m_ui->m_velocity,SIGNAL(toggled(bool)),this,SLOT(setVelocity(bool)));


  //set characteristics
  connect(m_ui->m_fluidity,SIGNAL(valueChanged(double)) ,this,SLOT(setFluidity(double)));
  connect(m_ui->m_plasticity,SIGNAL(valueChanged(double)),this,SLOT(setPlasticity(double)));
  connect(m_ui->m_elasticity,SIGNAL(valueChanged(double)),this,SLOT(setElasticity(double)));
  connect(m_ui->m_pressure,SIGNAL(valueChanged(double)),this,SLOT(setPressure(double)));
  connect(m_ui->m_density,SIGNAL(valueChanged(double)),this,SLOT(setDensity(double)));
  connect(m_ui->m_gravity,SIGNAL(valueChanged(double)),this,SLOT(scaleGravity(double)));
  connect(m_ui->m_ir,SIGNAL(valueChanged(double)),this,SLOT(setInteractionRadius(double)));

  connect(m_ui->m_springs,SIGNAL(toggled(bool)),this,SLOT(toggleSprings(bool)));
  connect(m_ui->m_relaxation,SIGNAL(toggled(bool)),this,SLOT(toggleRelaxation(bool)));
  connect(m_ui->m_viscosity,SIGNAL(toggled(bool)),this,SLOT(toggleViscosity(bool)));


//  cancel and reset
  connect(m_ui->m_generate,SIGNAL(clicked(bool)),this,SLOT(generate(bool)));
  connect(m_ui->m_reset,SIGNAL(clicked(bool)),this,SLOT(stopSimulation(bool)));


}

MainWindow::~MainWindow()
{
    delete m_ui;
}
