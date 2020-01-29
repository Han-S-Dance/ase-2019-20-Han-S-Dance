#pragma once

#include <World.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>

#include <QOpenGLWindow>
#include <QKeyEvent>
#include <QTimerEvent>
#include "WindowParams.h"

#include <QOpenGLWidget>

class NGLScene : public QOpenGLWindow
{
    Q_OBJECT

    private:
        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;
        ngl::Mat4 m_transform;

        World m_world;
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


    public:
        NGLScene();

        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int _w, int _h) override;

        ~NGLScene() noexcept override = default ;

};
