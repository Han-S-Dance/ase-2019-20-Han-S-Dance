#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <QGuiApplication>

NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent )
{
  setFocus();
  this->resize(_parent->size());
  m_world = World(0,1,false);
}

void NGLScene::resizeGL( int _w, int _h )
{
    m_win.width  = static_cast<int>( _w * devicePixelRatio() );
    m_win.height = static_cast<int>( _h * devicePixelRatio() );
    m_projection=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.1f, 80.0f );
}

void NGLScene::initializeGL()
{
    ngl::NGLInit::instance();
    glClearColor( 0.12f, 0.12f, 0.12f, 1.0f );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_MULTISAMPLE );
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ngl::Vec3 eye{ 0.0f, 0.0f, -3.9f };
    m_view=ngl::lookAt(eye,ngl::Vec3::zero(),ngl::Vec3::up());
    ngl::VAOPrimitives *prim =  ngl::VAOPrimitives::instance();
    prim->createSphere("particle", 0.012f, 10);
    prim->createSphere("Tank", m_world._tank.radius, 40);

    m_timer =startTimer(1);

}

void NGLScene::loadMatricesToShader(ngl::Transformation &_tx)
{
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  shader->use(ngl::nglColourShader);
  shader->setUniform("MVP", m_projection*m_view*m_globalMouseTX*_tx.getMatrix());

}

void NGLScene::paintGL()
{
  glViewport(0,0,m_win.width,m_win.height);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  shader ->use(ngl::nglColourShader);
  ngl::Mat4 rotX,rotY;
  rotX.rotateX(m_win.spinXFace);
  rotY.rotateY(m_win.spinYFace);
  m_globalMouseTX=rotX*rotY;
  m_globalMouseTX.m_30=m_modelPos.m_x;
  m_globalMouseTX.m_31=m_modelPos.m_y;
  m_globalMouseTX.m_32=m_modelPos.m_z;

  ngl::Transformation tx;

  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();

  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
  m_transform.identity();
  loadMatricesToShader(tx);
  shader->setUniform("Colour",1.0f,1.0f,1.0f,0.1f);
  prim->draw( "Tank" );

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

  for (auto &v:m_world.particle_list)
    {

        tx.reset();
        tx.setPosition(v.get_position());
        shader->setUniform("Colour",0.2f,0.8f,0.2f,0.5f);
        loadMatricesToShader(tx);
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



void NGLScene::toggleViscosity(bool _trigger)
{
    if (_trigger == true)
    {
        m_world.apply_viscosity();
        m_viscositytoggle = true;
    }
    else{m_viscositytoggle = false;}
}

void NGLScene::toggleSprings(bool _trigger)
{
    if (_trigger == true)
    {
        m_world.spring_displacements();
        m_springstoggle = true;
    }
    else {m_springstoggle = false;}
}

void NGLScene::toggleRelaxation(bool _trigger)
{
    if (_trigger == true)
    {
        m_world.double_density_relaxation();
        m_relaxtoggle = true;
    }
    else {m_relaxtoggle = false;}
}


void NGLScene::stopSimulation(bool _trigger)
{
    if (_trigger == false)
        killTimer(m_timer);

}

void NGLScene::reset(bool _trigger)
{
    if (_trigger ==false)
    {
        killTimer(m_timer);
        m_world = World(static_cast<unsigned int>(m_pnumber),m_spread,m_randvelocity);
        m_timer =startTimer(1);
    }

}

void NGLScene::particleNumber(int _number)
{

    m_pnumber = _number;

}

void NGLScene::setSpread(double _s)
{
    m_spread = static_cast<float>(_s);
}


void NGLScene::randVelocity(bool _rv)
{
    m_randvelocity = _rv;
}


void NGLScene::timerEvent(QTimerEvent *)
{   
    reset(m_reset);
    m_world.apply_gravity();
    toggleViscosity(m_viscositytoggle);
    m_world.update_position();
    m_world.update_map();
    toggleSprings(m_springstoggle);
    toggleRelaxation(m_relaxtoggle);
    m_world.resolve_tank_collision();
    m_world.predict_velocity();
    update();
    stopSimulation(m_timerstop);
}


