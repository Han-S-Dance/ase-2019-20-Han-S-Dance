#include "NGLScene.h"
#include <QtGui/QGuiApplication>
#include <iostream>


int main(int argc, char** argv)
{
      QGuiApplication app(argc, argv);

      QSurfaceFormat format;

      format.setSamples(4);
    #if defined(__APPLE__)

      format.setMajorVersion(4);
      format.setMinorVersion(1);
    #else

      format.setMajorVersion(4);
      format.setMinorVersion(5);
    #endif

      format.setProfile(QSurfaceFormat::CoreProfile);

      format.setDepthBufferSize(24);

      QSurfaceFormat::setDefaultFormat(format);


      NGLScene window;


      std::cout << "Profile is " << format.majorVersion() << " " << format.minorVersion() << "\n";
      // set the window size
      window.resize(1024, 720);

      window.show();
      return app.exec();
}
