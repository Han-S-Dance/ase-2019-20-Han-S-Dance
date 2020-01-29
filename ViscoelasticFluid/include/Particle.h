#ifndef Particle_H
#define Particle_H

#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <map>

class Particle
{
  public :
    Particle(ngl::Vec3 _position, ngl::Vec3 _velocity);
    Particle()=default;
    ~Particle() noexcept =default;
    Particle(const Particle &)=default;
    Particle & operator=(const Particle &)=default;
    Particle(Particle &&)=default;
    Particle & operator=(Particle &&)=default;


    std::map<int,float> _springs;

    void set_position(ngl::Vec3);
    void setX_position(float);
    void setY_position(float);
    void setZ_position(float);
    const ngl::Vec3 &get_position() const noexcept;
    void update_lastposition();
    ngl::Vec3 get_lastposition();
    void set_velocity(ngl::Vec3);
    const ngl::Vec3 &get_velocity() const noexcept;




 private :

    ngl::Vec3 m_position;
    ngl::Vec3 m_lastposition;
    ngl::Vec3 m_velocity;



};

#endif
