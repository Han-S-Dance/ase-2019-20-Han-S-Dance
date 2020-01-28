TARGET=ViscoelasticFluidTests

HEADERS+=../include/Particle.h ../include/World.h  ../include/Tank.h
INCLUDEPATH =+ ../include



SOURCES+= WorldTests.cpp  ../src/World.cpp
SOURCES+= ParticleTests.cpp ../src/Particle.cpp
SOURCES+= TankTests.cpp ../src/Tank.cpp


CONFIG-=app_bundle
QMAKE_CXXFLAGS += -std=c++1z
QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CXXFLAGS += -g

LIBS+= -L/usr/local/lib -lgtest -lgtest_main -pthread

NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
         win32:include($(HOMEDRIVE)\$(HOMEPATH)\NGL\UseNGL.pri)

}
else{
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}
