///
///  @file Particle.cpp
///  @brief Creates a particle with different attributes.


#include <iostream>
#include "Particle.h"

//Additional File Includes
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>


Particle::Particle(ngl::Vec3 _position, ngl::Vec3 _velocity)
{
    m_position =_position;
    m_velocity = _velocity;
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

const ngl::Vec3 &Particle::get_position() const noexcept
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


const ngl::Vec3 &Particle::get_velocity() const noexcept
{
    return m_velocity;
}

