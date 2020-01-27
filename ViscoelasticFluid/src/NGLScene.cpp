#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <QGuiApplication>
NGLScene::NGLScene() :  m_world(100,ngl::Vec3(0.0f,8.4f,0.0f))
{
    setTitle( "Viscoelastic Fluid Simulation Demo" );
}
void NGLScene::resizeGL( int _w, int _h )
{
    m_projection=ngl::perspective( 13.0f, static_cast<float>( _w ) / _h, 1.0f, 200.0f );
}
void NGLScene::initializeGL()
{
    ngl::NGLInit::instance();
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_MULTISAMPLE );
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ngl::Vec3 eye{ 60.0f, 60.0f, 60.0f };
    m_view=ngl::lookAt(eye,ngl::Vec3::zero(),ngl::Vec3::up());
    ngl::VAOPrimitives *prim =  ngl::VAOPrimitives::instance();
    prim->createSphere("particle", 0.05f, 10);
    prim->createSphere("Tank", m_world._tank.radius, 40);

    startTimer(1);
}
void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  shader->use(ngl::nglColourShader);

   ngl::Mat4 MVP = m_projection * m_view * m_transform;
   shader->setUniform("MVP",MVP);

}
void NGLScene::paintGL()
{
  glViewport( 0, 0, width(), height() );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  shader ->use(ngl::nglColourShader);

  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();

  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
  m_transform.identity();
  loadMatricesToShader();
  shader->setUniform("Colour",1.0f,1.0f,1.0f,0.1f);
  //prim->draw( "Tank" );

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

  for (auto &v:m_world.particle_list)
  {
      m_transform.identity();
      ngl::Vec3 tp = v.get_position();
      m_transform.translate(tp.m_x,tp.m_y,tp.m_z);
      shader->setUniform("Colour",0.f,1.f,0.f,0.5f);
      loadMatricesToShader();
      prim->draw( "particle" );

  }
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::keyPressEvent( QKeyEvent* _event )
{

  switch ( _event->key() )
  {
    case Qt::Key_Escape:
      QGuiApplication::exit( EXIT_SUCCESS );
      break;

    default:
      break;
  }
  update();
}


void NGLScene::timerEvent(QTimerEvent *)
{
    m_world.apply_gravity();
    m_world.apply_viscosity();
    m_world.update_position();
    m_world.spring_displacements();
    m_world.double_density_relaxation();
    m_world.resolve_tank_collision();
    m_world.predict_velocity();
    update();
}




