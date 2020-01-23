#include "Particle.h"
#include <iostream>
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>


ngl::Vec3 Particle::position()
{
    return m_position;
}

ngl::Vec3 Particle::lastposition()
{
    return m_lastposition;
}

ngl::Vec3 Particle::velocity()
{
    return m_velocity;
}

std::map<Particle*,float> Particle::neighbour()
{
    return m_neighbour;
}


std::map<Particle*,float> Particle::spring()
{
    return m_spring;
}

Particle::Particle(ngl::Vec3 _position)
{
    m_position=_position;
}

void Particle::set_position(ngl::Vec3 _newposition)
{
    m_position=_newposition;
}

ngl::Vec3 Particle::get_position()
{
    return m_position;
}

void Particle::update_lastposition()
{
    m_lastposition = get_position();
}


ngl::Vec3 Particle::get_lastposition()
{

    return m_lastposition;
}

void Particle::set_velocity(ngl::Vec3 _newvelocity)
{
    m_velocity = _newvelocity;
}


ngl::Vec3 Particle::get_velocity()
{
    return m_velocity;
}

//operator overload of == to compare 2 particles.
//bool Particle::operator==(const Particle &_v) const noexcept
//{
//    return (
//                  m_position == _v.m_position &&
//                  m_lastposition == _v.m_lastposition &&
//                  m_velocity == _v.m_velocity
//            );
//}
