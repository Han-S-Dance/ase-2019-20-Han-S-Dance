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

void Particle::setX_position(float _newX)
{
    m_position = ngl::Vec3(_newX,m_position[1],m_position[2]);
}

void Particle::setY_position(float _newY)
{
    m_position = ngl::Vec3(m_position[0],_newY,m_position[2]);
}

void Particle::setZ_position(float _newZ)
{
    m_position = ngl::Vec3(m_position[0],m_position[1],_newZ);
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
