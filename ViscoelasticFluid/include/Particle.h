#ifndef Particle_H
#define Particle_H

#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <map>

class Particle
{
  public :
    Particle(ngl::Vec3 _position);//, std::map<Particle*,float> _spring);
    Particle()=default;
    ~Particle() noexcept =default;
    Particle(const Particle &)=default;
    Particle & operator=(const Particle &)=default;
    Particle(Particle &&)=default;
    Particle & operator=(Particle &&)=default;
    ngl::Vec3 position();
    ngl::Vec3 lastposition();
    ngl::Vec3 velocity();
    std::map<Particle*,float> neighbour();
    std::map<Particle*,float> spring();

    //bool operator==(const Particle &_v) const noexcept;


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
    std::map<Particle*,float> m_neighbour;
    std::map<Particle*,float> m_spring;


};

#endif
