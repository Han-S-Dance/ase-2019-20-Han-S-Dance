#ifndef Particle_H
#define Particle_H
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>

class Particle
{
  public :
    Particle(ngl::Vec3 _position, ngl::Vec3 _lastposition, ngl::Vec3 _velocity);
    Particle()=default;
    ~Particle() noexcept =default;
    Particle(const Particle &)=default;
    Particle & operator=(const Particle &)=default;
    Particle(Particle &&)=default;
    Particle & operator=(Particle &&)=default;
    ngl::Vec3 position();
    ngl::Vec3 lastposition();
    ngl::Vec3 velocity();

    bool operator==(const Particle &_v) const noexcept;


    void set_position(ngl::Vec3);
    ngl::Vec3 get_position();
    void update_lastposition();
    ngl::Vec3 get_lastposition();
    void set_velocity(ngl::Vec3);
    ngl::Vec3 get_velocity();



 private :

    ngl::Vec3 m_position;
    ngl::Vec3 m_lastposition;
    ngl::Vec3 m_velocity;

};

#endif
