﻿#include "World.h"
#include <iostream>
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <Particle.h>
#include <algorithm>
#include "Tank.h"
#include <math.h>

static constexpr float time_step = 0.03333333f;
//const float interaction_radius = 0.2f;

World::World(unsigned int number_particles, ngl::Vec3 particle_position)
{
    ngl::Random *rand = ngl::Random::instance();
    rand -> setSeed();

    _tank = Tank(1.2f);
    cube_size = 0.4f;
    for (unsigned int i=0 ;i<number_particles ; ++i)
    {
        float tr = _tank.radius;
        ngl::Vec3 new_posn;
        do
        {
            new_posn = rand->getRandomPoint(tr,tr,tr);
        } while(new_posn.length()>tr);

        particle_list.emplace_back(new_posn);
    }

    update_map();
}


void World::apply_gravity()
{
    for(auto &&v :particle_list)
        v.set_velocity( v.get_velocity() + time_step * ngl::Vec3(0.0f,-9.8f,0.0f) );
}

void World::update_position()
{
    for(auto &&v : particle_list)
    {
        v.update_lastposition();
        v.set_velocity(ngl::Vec3::up());
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


std::size_t World::hash_function(float _value, float _min_value, float _division_size)
{
    float cubes = _value - _min_value;
    float divisions = 1.f/_division_size;

    auto hash = (cubes*divisions)+0.5f*_division_size;
    std::cout<< hash << " = " << floor(hash) << " = " << static_cast<std::size_t>(hash) <<std::endl;
    return static_cast<std::size_t>(hash);
}


void World::update_map()
{
    auto minmax_x = std::minmax_element(std::begin(particle_list), std::end(particle_list), [&](const Particle &p1, const Particle &p2)
                                                                                            {
                                                                                                return (p1.get_position().m_x < p2.get_position().m_x);
                                                                                            });
    auto minmax_y = std::minmax_element(std::begin(particle_list), std::end(particle_list), [&](const Particle &p1, const Particle &p2)
                                                                                            {
                                                                                                return (p1.get_position().m_y < p2.get_position().m_y);
                                                                                            });
    auto minmax_z = std::minmax_element(std::begin(particle_list), std::end(particle_list), [&](const Particle &p1, const Particle &p2)
                                                                                            {
                                                                                                return (p1.get_position().m_z < p2.get_position().m_z);
                                                                                            });

    minx = minmax_x.first->get_position().m_x;
    miny = minmax_y.first->get_position().m_y;
    minz = minmax_z.first->get_position().m_z;

    auto width = minmax_x.second->get_position().m_x - minx;
    auto height = minmax_y.second->get_position().m_y - miny;
    auto depth = minmax_z.second->get_position().m_z - minz;

    x_divisions = static_cast<std::size_t>(ceil((width+0.001f) * (1.f/cube_size)));
    y_divisions = static_cast<std::size_t>(ceil((height+0.001f) * (1.f/cube_size)));
    std::size_t z_divisions = static_cast<std::size_t>(ceil((depth+0.001f) * (1.f/cube_size)));

    for (auto &&i : _spatial_map)
        i.clear();
    _spatial_map.clear();

    _spatial_map.resize(x_divisions*y_divisions*z_divisions);

    for(std::size_t i = 0; i<particle_list.size(); i++)
    {
        auto x = hash_function(particle_list[i].get_position()[0],minx,cube_size);
        auto y = hash_function(particle_list[i].get_position()[1],miny,cube_size);
        auto z = hash_function(particle_list[i].get_position()[2],minz,cube_size);

        std::size_t id = z*y_divisions*x_divisions +y*x_divisions + x; // VERIFY THE ID... WE GOT 237 / 216 once....
        if (id > _spatial_map.size())
            std::cout<< "(1) ======================> ERROR! id = " << id <<" / size = " << _spatial_map.size() << std::endl;
        else
            _spatial_map[id].emplace_back(i);
    }
}

std::vector<std::size_t> World:: map_neighbours(unsigned long i)
{
    auto x = hash_function(particle_list[i].get_position()[0],minx,cube_size);
    auto y = hash_function(particle_list[i].get_position()[1],miny,cube_size);
    auto z = hash_function(particle_list[i].get_position()[2],minz,cube_size);

    auto id = z*y_divisions*x_divisions +y*x_divisions + x;
    if (id > _spatial_map.size())
        std::cout<< "(2) ======================> ERROR! id = " << id <<" / size = " << _spatial_map.size() << std::endl;
    return _spatial_map[id];
}


std::vector<std::size_t> World::neighbours(std::size_t i, unsigned long _flag) //flag = 0 lists all neighbours after the particle in particle_list & flag = 1 list all neighbours
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
                    float distance = between_vector(particle_list[i].get_position(),particle_list[particle_id].get_position()).length();
                    if (distance < interaction_radius) //interection radius = 0.2
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

ngl::Vec3 World::linear_quadratic_impulses(float s, float u, ngl::Vec3 bv)
{
    ngl::Vec3 I = time_step*(1.0f-s)*(0.2f*u+0.1f*u*u)*bv;
    return (I/2);
}

void World::apply_viscosity()
{
    for(unsigned long i = 0; i<particle_list.size(); i++) //for each particle in particle_list
    {
        auto pneighs = neighbours(i,0);
        if (pneighs.size() > 0)
        {
            for(unsigned long j = 0; j<pneighs.size(); j++) //for each particle after the chosen particle in the list (pair)
            {
                unsigned long neigh = pneighs[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);

                if (bv.length() != 0.0f)
                {
                    float q = bv.length()/interaction_radius;
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
            //pneighs.clear();
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


ngl::Vec3 World::intersection_point(Particle P)
{
    auto L = -1*P.get_lastposition();
    auto v = between_vector(P.get_lastposition(),P.get_position());
    v.normalize();
    auto tca = L.dot(v);
    auto d2 = L.dot(L) - tca*tca;
    auto thc = sqrt(_tank.radius*_tank.radius -d2);
    auto t = tca + thc;
    auto Collision_Point = (P.get_lastposition() + t*v);
    return Collision_Point;

}

void World::resolve_tank_collision()
{
    for(unsigned long i = 0; i<particle_list.size(); i++) //for each particle in particle_list
    {
        if (outside_tank(particle_list[i]) == true)
        {
            ngl::Vec3 pos = intersection_point(particle_list[i]);
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
    for(unsigned long i = 0; i<particle_list.size(); i++)
    {
        float density =0;
        float near_density=0;
        std::vector<unsigned long> pneighs = neighbours(i,1);

        if (pneighs.size() > 0)
        {
            for(unsigned long j = 0; j<pneighs.size(); j++) //for each particle neighbour get density and near denisty
            {
                unsigned long neigh = pneighs[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);
                float q = bv.length()/interaction_radius;
                density += (1-q)*(1-q);
                near_density += (1-q)*(1-q)*(1-q);
            }

            float pressure = 0.004f*(density-3.0f); //rest density = 3.0f & stifness = 0.004
            float near_pressure = 0.01f*near_density; //stifness near = 0.01
            ngl::Vec3 dx;

            for(unsigned long j = 0; j<pneighs.size(); j++) //for each particle neighbour apply displacements
            {
                unsigned long neigh = pneighs[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);

                float q =0;
                auto length =bv.length();

                if (length != 0.0f)
                {
                    q = bv.length()/interaction_radius;
                    bv.normalize();
                }

                 ngl::Vec3 D = time_step*time_step*(pressure*(1-q) + near_pressure*(1-q)*(1-q))*bv;
                 particle_list[neigh].set_position(particle_list[neigh].get_position()+(D/2));
                 dx -= (D/2);
            }

            particle_list[i].set_position(particle_list[i].get_position()+dx);
        }
        //pneighs.clear();
    }
}

void World::add_deform_springs(unsigned long i)
{
    std::vector<unsigned long> pneighs = neighbours(i,0);
    if (pneighs.size() > 0)
    {

        for(unsigned long j = 0; j<pneighs.size(); j++) //for each particle neighbour
        {
            if (particle_list[i]._springs.count(static_cast<int>(j)) == 0) //no spring present
            {
                unsigned long neigh = pneighs[j]; //index in particle_list
                particle_list[i]._springs[static_cast<int>(neigh)] = 0.1f; //add spring length 0.1f
            }
        }

        for(std::map<int,float>::iterator it = particle_list[i]._springs.begin(); it !=particle_list[i]._springs.end(); it++) //iterate over spring map
        {
            ngl::Vec3 bv = between_vector(particle_list[i],particle_list[static_cast<unsigned long>(it->first)]);
            float d = 0.1f*it->second; //yield ratio =0.1
            float length = bv.length();
            if (length > (it->second + d))
            {
                it->second += time_step * 0.3f * (length - it->second - d);   //alpha/plasticity constant =0.3f
            }

            if (length < (it->second - d))
            {
                it->second -= time_step * 0.3f * (it->second - d - length);
            }
        }
        pneighs.clear();
    }
}

void World::remove_springs(unsigned long i)
{
   for(std::map<int,float>::iterator it = particle_list[i]._springs.begin(); it != particle_list[i]._springs.end(); it++)
   {
       int neigh = it->first;
       float dist = between_vector(particle_list[i],particle_list[static_cast<unsigned long>(neigh)]).length();
       if (dist >interaction_radius)
       {
           particle_list[i]._springs.erase(it);
       }
   }
}


void World::adjust_springs()
{
    for(unsigned long i = 0; i<particle_list.size(); i++)
    {
        remove_springs(i);

        add_deform_springs(i);
    }
}

void World::spring_displacements()
{
    adjust_springs();
    for(unsigned long i = 0; i<particle_list.size(); i++)
    {
        for(std::map<int,float>::iterator it = particle_list[i]._springs.begin(); it !=particle_list[i]._springs.end(); it++)
        {
            ngl::Vec3 bv = between_vector(particle_list[i],particle_list[static_cast<unsigned long>(it->first)]);
            ngl::Vec3 D = time_step*time_step*0.3f*(1-(it->second / interaction_radius))*(it->second - bv.length())*bv;  //kspring = 0.3f
            particle_list[i].set_position(particle_list[i].get_position()-(D/2.0f));
            particle_list[static_cast<unsigned long>(it->first)].set_position(particle_list[static_cast<unsigned long>(it->first)].get_position()+(D/2.0f));
        }
    }
}
