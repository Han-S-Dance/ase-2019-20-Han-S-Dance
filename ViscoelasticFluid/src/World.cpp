﻿///
///  @file World.cpp
///  @brief Holds the world of particles and the tank they live in. Calculates everything for the simulation.

#include "World.h"
#include <iostream>

//Additional File Includes
#include <math.h>
#include <ngl/Random.h>

static constexpr float time_step = 0.03333333f;

World::World(unsigned int _numParticles, float _spread, bool _randVelocity)
{
    ngl::Random *rand = ngl::Random::instance();
    rand -> setSeed();

    _tank = Tank(1.2f);
    cube_size = 0.6f;

    m_fluidity = 0.3f;
    m_plasticity = 0.3f;
    m_elasticity = 0.3f;
    m_density =3.0f;
    m_pressure = 0.1f;
    m_interaction_radius = 0.2f;
    m_gravityscale = 0.0f;

    float tr = _tank.radius;

    //assign each particle random position and veolcity
    //the position needs be in sphere hence while dolong
    for (unsigned int i=0 ;i<_numParticles ; ++i)
    {
        ngl::Vec3 new_veloc;
        if (_randVelocity == true)
        {
             new_veloc = rand->getRandomPoint(0.01f,0.01f,0.01f);
        }
        ngl::Vec3 new_posn;
        do
        {
            new_posn = _spread*rand->getRandomPoint(tr,tr,tr);
        } while(new_posn.length()>tr);

        particle_list.push_back(Particle(new_posn,new_veloc));
    }

    update_map();
}


void World::apply_gravity()
{
    for(auto &&v :particle_list)
        v.set_velocity( v.get_velocity() + time_step * ngl::Vec3(0.0f,-9.8f,0.0f) *m_gravityscale );
}

void World::update_position()
{
    for(auto &&v : particle_list)
    {
        v.update_lastposition();
        v.set_position(v.get_position() + time_step * v.get_velocity());
    }
}

void World::predict_velocity()
{
    for(Particle &v: particle_list)
    {
       v.set_velocity((v.get_position()-v.get_lastposition())/time_step);
    }

}


ngl::Vec3 World::between_vector(Particle p, Particle q) //vector from p to q
{
    auto bv = q.get_position() - p.get_position();
    return bv;
}


std::tuple<int,int,int> World::hash_function(ngl::Vec3 _position)
{
    auto hash_x = floor(_position.m_x *(1.0f/cube_size));
    auto hash_y = floor(_position.m_y *(1.0f/cube_size));
    auto hash_z = floor(_position.m_z *(1.0f/cube_size));

    return std::make_tuple(hash_x,hash_y,hash_z);
}


void World::update_map()
{
    _spatial_map.clear();
    for(std::size_t i=0; i<particle_list.size(); i++)
    {
        auto hash = hash_function(particle_list[i].get_position());
        auto count = 0;

        //initialise spatial cubes only when particles are in them - need check if exists or nor
        //if does not exist create a vector list with the index.
        //if does exist create push index into i into vector.

        for (auto it = _spatial_map.begin(); it != _spatial_map.end(); ++it)
        {
            if(it->first == hash)
            {
                it->second.push_back(i);
                count++;
            }
        }

        if(count == 0)
        {
            std::vector<size_t> list;
            list.push_back(i);
            _spatial_map.insert(std::make_pair(hash,list));

        }
    }
}


//gathers all particles in same spatial cube as chosen particle index
std::vector<std::size_t> World:: map_neighbours(std::size_t i)
{
    std::vector<std::size_t> neighbours;
    auto hash = hash_function(particle_list[i].get_position());
    for (auto it = _spatial_map.begin(); it != _spatial_map.end(); ++it)
    {
        if(it->first ==hash)
        neighbours = it->second;
    }
    return neighbours;
}


//finds all neighbours for a particle i
//flag = 0 lists all neighbours after the particle in particle_list & flag = 1 list all neighbours
std::vector<std::size_t> World::neighbours(std::size_t i, std::size_t _flag)
{
    std::vector<std::size_t> neighbours;
    auto map_neighbour = map_neighbours(i);

    auto neighbour_size = map_neighbour.size();
    for(std::size_t j=0; j<neighbour_size ; ++j)
    {
        auto particle_id = map_neighbour[j];
        if (i == particle_id)
            continue;
        else
        {
            if((_flag == 0) && (particle_id<i))
                continue;
            else
                {

                    float distance = between_vector(particle_list[i],particle_list[particle_id]).length();
                    if (distance < m_interaction_radius) //interection radius = 0.2
                        neighbours.push_back(particle_id);
                }
        }
    }
    return neighbours;
}


float World::inward_radial_veloctiy(Particle p, Particle q, ngl::Vec3 unit_vec)
{
    float u = (p.get_velocity()-q.get_velocity()).dot(unit_vec);
    return u;
}

ngl::Vec3 World::linear_quadratic_impulses(float r, float u, ngl::Vec3 bv)
{
    ngl::Vec3 I = time_step*(1.0f-r)*(m_fluidity*u+0.1f*u*u)*bv;
    return (I/2);
}

void World::apply_viscosity()
{
    for(std::size_t i = 0; i<particle_list.size(); i++) //for each particle in particle_list
    {
        auto pneighs = neighbours(i,0);
        if (pneighs.size() > 0)
        {
            for(std::size_t j = 0; j<pneighs.size(); j++) //for each particle after the chosen particle in the list (pair)
            {
                std::size_t neigh = pneighs[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);

                if (bv.length() != 0.0f)
                {
                    float q = bv.length()/m_interaction_radius;
                    bv.normalize();

                    float u = inward_radial_veloctiy(particle_list[i], particle_list[neigh], bv);
                    if (u > 0)
                    {
                        auto I = linear_quadratic_impulses(q,u,bv);
                        particle_list[i].set_velocity(particle_list[i].get_velocity()-I);
                        particle_list[neigh].set_velocity(particle_list[neigh].get_velocity()+I);
                    }
                }
            }
            pneighs.clear();
        }
    }
}


bool World::outside_tank(Particle P)
{
 auto distance = P.get_position().length();
 if (distance > _tank.radius)
     return true;
 else
     return false;
}

//sphere and ray interesction formula
ngl::Vec3 World::intersection_point(Particle P)
{
    auto L = -1*P.get_lastposition();
    auto v = P.get_position() - P.get_lastposition();
    v.normalize();
    auto tca = L.dot(v);
    auto d2 = L.dot(L) - tca*tca;
    auto thc =0.0f;
    auto check = _tank.radius*_tank.radius -d2;
    if (check > 0.000001f)
    {
        thc = sqrt(check);
    }
    auto t = tca + thc;
    auto Collision_Point = (P.get_lastposition() + t*v);
    return Collision_Point;

}

void World::resolve_tank_collision()
{
    for(std::size_t i = 0; i<particle_list.size(); i++) //for each particle in particle_list
    {

        if (outside_tank(particle_list[i]) == true)
        {
            ngl::Vec3 pos = intersection_point(particle_list[i]);;
            auto container_normal = -1*pos;
            container_normal.normalize();
            auto vel = (pos - particle_list[i].get_lastposition())/time_step;
            auto Impulse = (vel.dot(container_normal))*container_normal;

            particle_list[i].set_position(pos-(Impulse*time_step));
        }
    }
}



void World::double_density_relaxation()
{
    float near_stiffness = m_pressure/10.0f;
    float stiffness = m_pressure/25.0f;

    for(std::size_t i = 0; i<particle_list.size(); i++)
    {
        float density =0;
        float near_density=0;
        std::vector<std::size_t> pneighs = neighbours(i,1);

        if (pneighs.size() > 0)
        {
            for(std::size_t j = 0; j<pneighs.size(); j++) //for each particle neighbour get density and near denisty
            {
                std::size_t neigh = pneighs[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);
                float q = bv.length()/m_interaction_radius;
                density += (1-q)*(1-q);
                near_density += (1-q)*(1-q)*(1-q);
            }

            float pressure = stiffness*(density-m_density); //rest density = 3.0f & stifness = 0.004
            float near_pressure = near_stiffness*near_density; //stifness near = 0.01
            ngl::Vec3 dx;

            for(std::size_t j = 0; j<pneighs.size(); j++) //for each particle neighbour apply displacements
            {
                std::size_t neigh = pneighs[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);

                float q =0;
                auto length =bv.length();

                if (length != 0.0f)
                {
                    q = bv.length()/m_interaction_radius;
                    bv.normalize();
                }

                 ngl::Vec3 D = time_step*time_step*(pressure*(1-q) + near_pressure*(1-q)*(1-q))*bv;
                 particle_list[neigh].set_position(particle_list[neigh].get_position()+(D/2));
                 dx -= (D/2);
            }

            particle_list[i].set_position(particle_list[i].get_position()+dx);
        }
        pneighs.clear();
    }
}

void World::add_deform_springs(std::size_t i)
{
    std::vector<std::size_t> pneighs = neighbours(i,0);
    if (pneighs.size() > 0)
    {

        for(std::size_t j = 0; j<pneighs.size(); j++) //for each particle neighbour
        {
            if (particle_list[i]._springs.count(static_cast<int>(j)) == 0) //no spring present
            {
                std::size_t neigh = pneighs[j]; //index in particle_list
                particle_list[i]._springs[static_cast<int>(neigh)] = 0.1f; //add spring length 0.1f
            }
        }

        for(std::map<int,float>::iterator it = particle_list[i]._springs.begin(); it !=particle_list[i]._springs.end(); it++) //iterate over spring map
        {
            ngl::Vec3 bv = between_vector(particle_list[i],particle_list[static_cast<std::size_t>(it->first)]);
            float d = 0.1f*it->second; //yield ratio =0.1
            float length = bv.length();
            if (length > (it->second + d))
            {
                it->second += time_step * m_plasticity * (length - it->second - d);   //alpha/plasticity constant =0.3f
            }

            if (length < (it->second - d))
            {
                it->second -= time_step * m_plasticity * (it->second - d - length);
            }
        }
        pneighs.clear();
    }
}

void World::remove_springs(std::size_t i)
{
   for(std::map<int,float>::iterator it = particle_list[i]._springs.begin(); it != particle_list[i]._springs.end(); it++)
   {
       int neigh = it->first;
       float dist = between_vector(particle_list[i],particle_list[static_cast<std::size_t>(neigh)]).length();
       if (dist >m_interaction_radius)
       {
           particle_list[i]._springs.erase(it);
       }
   }
}


void World::adjust_springs()
{
    for(std::size_t i = 0; i<particle_list.size(); i++)
    {
        remove_springs(i);

        add_deform_springs(i);
    }
}

void World::spring_displacements()
{
    adjust_springs();
    for(std::size_t i = 0; i<particle_list.size(); i++)
    {
        for(std::map<int,float>::iterator it = particle_list[i]._springs.begin(); it !=particle_list[i]._springs.end(); it++)
        {
            ngl::Vec3 bv = between_vector(particle_list[i],particle_list[static_cast<std::size_t>(it->first)]);
            ngl::Vec3 D = time_step*time_step*m_elasticity*(1-(it->second / m_interaction_radius))*(it->second - bv.length())*bv;
            particle_list[i].set_position(particle_list[i].get_position()-(D/2.0f));
            particle_list[static_cast<std::size_t>(it->first)].set_position(particle_list[static_cast<std::size_t>(it->first)].get_position()+(D/2.0f));
        }
    }
}


void World::setFluidity(double _f) //_f
{
    m_fluidity = static_cast<float>(_f);
}

void World::setPlasticity(double _p)
{
    m_plasticity = static_cast<float>(_p);
}

void World::setElasticity(double _e)
{
    m_elasticity = static_cast<float>(_e);
}

void World::setDensity(double _d)
{
    m_density = static_cast<float>(_d);
}

void World::setPressure(double _p)
{
    m_pressure = static_cast<float>(_p);
}

void World::setInteractionRadius(double _i)
{
    m_interaction_radius =static_cast<float>(_i);
}

void World::scaleGravity(double _g)
{
    m_gravityscale = static_cast<float>(_g);
}
