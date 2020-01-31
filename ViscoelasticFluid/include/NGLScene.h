#pragma once

#include <World.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimerEvent>
#include <memory>
#include "WindowParams.h"


class NGLScene : public QOpenGLWidget
{
    Q_OBJECT

    private:
        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;
        ngl::Mat4 m_transform;
        ngl::Vec3 m_modelPos;
        ngl::Mat4 m_globalMouseTX;

    private:
        void loadMatricesToShader(ngl::Transformation &_tx);
        void keyPressEvent(QKeyEvent *_event) override;
        void timerEvent(QTimerEvent*) override;
        void mouseMoveEvent (QMouseEvent * _event ) override;
        void mousePressEvent ( QMouseEvent *_event) override;
        void mouseReleaseEvent ( QMouseEvent *_event ) override;
        void wheelEvent( QWheelEvent *_event) override;

        WinParams m_win;

    private:
        bool m_viscositytoggle =true;
        bool m_springstoggle =true;
        bool m_relaxtoggle =true;
        bool m_timerstop = true;
        bool m_randvelocity = true;

        int m_pnumber;
        int m_reset = true;
        int m_timer;

        float m_spread;

    public:
        NGLScene(QWidget *_parent);

        World m_world;

        void createScene(bool);

        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int _w, int _h) override;

        ~NGLScene() noexcept override = default ;

        void toggleViscosity(bool);
        void toggleSprings(bool);
        void toggleRelaxation(bool);

        void stopSimulation(bool);        
        void reset(bool);

        void particleNumber(int);
        void setSpread(double);
        void randVelocity(bool);

};
