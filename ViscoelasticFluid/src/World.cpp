#include "World.h"
#include <iostream>
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <Particle.h>
#include <algorithm>
#include "Tank.h"
#include <math.h>

const float time_step = 0.03333333f;
//const float interaction_radius = 0.2f;

World::World(unsigned int number_particles, ngl::Vec3 particle_position)
{

    ngl::Random *rand = ngl::Random::instance();
    rand -> setSeed();

    for (unsigned int i=0 ;i<number_particles ; ++i)
    {
        float tr = _tank.radius;
        ngl::Vec3 new_posn = ngl::Vec3() +1.0f*rand->getRandomPoint(tr,tr,tr);
        while(new_posn.length()>tr)
        {
            auto updated_posn = ngl::Vec3() +1.0f*rand->getRandomPoint(tr,tr,tr);
            new_posn = updated_posn;
        }

        particle_list.push_back(Particle(new_posn));
    }

    update_map();
}


void World::apply_gravity()
{
    for(Particle &v :particle_list)
        v.set_velocity(v.get_velocity() + time_step* ngl::Vec3(0.0f,-9.8f,0.0f));
}

void World::update_position()
{
    for(Particle &v: particle_list)
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


int World::hash_function(float _value, float _min_value, float _division_size)
{

    float cubes = _value - _min_value;
    float divisions = 1/_division_size;

    int hash = static_cast<int>(floor((cubes*divisions)+0.5f*_division_size));

    return hash;
}


void World::update_map()
{

    for(std::vector<int> &i: _spatial_map) //clear the map
    {
        i.clear();
    }

    std::vector<Particle> sorted_x = particle_list;
    std::vector<Particle> sorted_y = particle_list;
    std::vector<Particle> sorted_z = particle_list;


    sort(sorted_x.begin(), sorted_x.end(),[](Particle p, Particle q) {return p.get_position().m_x<q.get_position().m_x;});
    sort(sorted_y.begin(), sorted_y.end(),[](Particle p, Particle q) {return p.get_position().m_y<q.get_position().m_y;});
    sort(sorted_z.begin(), sorted_z.end(),[](Particle p, Particle q) {return p.get_position().m_z<q.get_position().m_z;});

    unsigned long list_size = particle_list.size();
    minx = sorted_x[0].get_position()[0];
    auto maxx = sorted_x[list_size-1].get_position()[0];
    miny = sorted_y[0].get_position()[1];
    auto maxy = sorted_y[list_size-1].get_position()[1];
    minz = sorted_z[0].get_position()[2];
    auto maxz = sorted_z[list_size-1].get_position()[2];

    auto width = maxx - minx;
    auto height = maxy - miny;
    auto depth = maxz - minz;

    x_divisions = ceil((width+0.001f) * (1/cube_size));
    y_divisions = ceil((height+0.001f) * (1/cube_size));
    auto z_divisions = ceil((depth+0.001f) * (1/cube_size));


    _spatial_map.resize(static_cast<unsigned long>((x_divisions*y_divisions*z_divisions)));

    for(unsigned long i = 0; i<particle_list.size(); i++)
    {
        int x = hash_function(particle_list[i].get_position()[0],minx,cube_size);
        int y = hash_function(particle_list[i].get_position()[1],miny,cube_size);
        int z = hash_function(particle_list[i].get_position()[2],minz,cube_size);

        auto id = z*y_divisions*x_divisions +y*x_divisions + x;
        _spatial_map[static_cast<unsigned long>(id)].push_back(static_cast<int>(i));

    }
}

std::vector<int> World:: map_neighbours(unsigned long i)
{
    int x = hash_function(particle_list[i].get_position()[0],minx,cube_size);
    int y = hash_function(particle_list[i].get_position()[1],miny,cube_size);
    int z = hash_function(particle_list[i].get_position()[2],minz,cube_size);

    auto id = z*y_divisions*x_divisions +y*x_divisions + x;
    std::vector<int> list = _spatial_map[static_cast<unsigned long>(id)];
    return list;
}


std::vector<unsigned long> World::neighbours(unsigned long i, unsigned long m_flag) //flag = 0 lists all neighbours after the particle in particle_list & flag = 1 list all neighbours
{

    std::vector<unsigned long> neighbours;
    std::vector<int> same_container = map_neighbours(i);

    for(unsigned long j=0; j<same_container.size() ; ++j)
    {

        unsigned long particle_id = static_cast<unsigned long>(same_container[j]);
        if (i == particle_id)
            continue;
        else
        {
            if((m_flag == 0) && (particle_id<i))
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
        std::vector<unsigned long> pneighs = neighbours(i,0);
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
