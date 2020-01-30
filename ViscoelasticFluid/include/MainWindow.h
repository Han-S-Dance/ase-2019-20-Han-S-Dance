#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NGLScene.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *m_ui;
        /// @brief our openGL widget
    NGLScene *m_gl;


private slots:

    inline void setFluidity(double _f){m_gl->m_world.setFluidity(_f);}
    inline void setPlasticity(double _p){m_gl->m_world.setPlasticity(_p);}
    inline void setElasticity(double _e){m_gl->m_world.setElasticity(_e);}
    inline void setDensity(double _d){m_gl->m_world.setDensity(_d);}
    inline void setPressure(double _p){m_gl->m_world.setPressure(_p);}
    inline void scaleGravity(double _g){m_gl->m_world.scaleGravity(_g);}
    inline void setInteractionRadius(double _i){m_gl->m_world.setInteractionRadius(_i);}

    inline void toggleViscosity(bool _v){m_gl->toggleViscosity(_v);}
    inline void toggleSprings(bool _s){m_gl->toggleSprings(_s);}
    inline void toggleRelaxation(bool _r){m_gl->toggleRelaxation(_r);}

    inline void stopSimulation(bool _r){m_gl->stopSimulation(_r);}

    inline void setParticleNumber(int _p){m_gl->particleNumber(_p);}
    inline void setSpread(double _s){m_gl->setSpread(_s);}
    inline void setVelocity(bool _v){m_gl->randVelocity(_v);}
    inline void generate(bool _g){m_gl->reset(_g);}

};

#endif // MAINWINDOW_H
