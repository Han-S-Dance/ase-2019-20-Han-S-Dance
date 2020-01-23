#pragma once

#include <World.h>
#include <ngl/Mat4.h>

#include <QOpenGLWindow>
#include <QKeyEvent>
#include <QTimerEvent>

class NGLScene : public QOpenGLWindow
{
    Q_OBJECT

    private:
        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;
        ngl::Mat4 m_transform;

        World m_world;

    private:
        void loadMatricesToShader();
        void keyPressEvent(QKeyEvent *_event) override;
        void timerEvent(QTimerEvent*) override;


    public:
        NGLScene();

        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int _w, int _h) override;

        ~NGLScene() noexcept override = default ;

};
