#include "World.h"
#include <iostream>
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <Particle.h>
#include <ngl/Random.h>
#include <algorithm>
#include "Tank.h"

//used a "time step" of 2 here need to update this

World::World(unsigned int number_particles, ngl::Vec3 particle_position)
{

    ngl::Random *rand = ngl::Random::instance();
    rand -> setSeed();

    for (unsigned int i=0 ;i<number_particles ; ++i)
    {
        ngl::Vec3 new_posn = particle_position + rand->getRandomNormalizedVec3();

        particle_list.push_back(Particle(new_posn));
    }

}

const float time_step = 0.03333333f;
//void World::generate_particles(unsigned int number_particles, ngl::Vec3 start_position) // might need change this to give particles not just the number they need.
//{
//    for (unsigned int i=0 ;i<number_particles ; ++i)
//    {
//        particle_list.push_back(Particle(start_position));
//    }

//}

void World::apply_gravity()
{
    for(Particle &v :particle_list)
        v.set_velocity(v.get_velocity() + time_step* ngl::Vec3(0.0f,-9.8f,0.0f)); //need to do something about this time step of 2
}

void World::update_position()
{
    for(Particle &v: particle_list)
    {
        v.update_lastposition();
        v.set_position(v.get_position() + time_step * v.get_velocity()); //need to do something about this time step of 2
    }
}

void World::predict_velocity()
{
    for(Particle &v: particle_list)
    {
       v.set_velocity((v.get_position()-v.get_lastposition())/time_step); //need to do something about this time step of 2
    }

}


ngl::Vec3 World::between_vector(Particle p, Particle q) //vector from p to q
{
    auto bv = q.get_position() - p.get_position();
    return bv;
}

void World::neighbours(unsigned long i, unsigned long m_flag = 0) //flag = 0 lists all neighbours after the particle in particle_list & flag = 1 list all neighbours
{

    unsigned long start =0;
    if (m_flag == 0)
    {
        start=i;
    }

    for(unsigned long j =start; j<particle_list.size() ; ++j)
    {
        if (i ==j)
            continue;
        else
        {
            float distance = between_vector(particle_list[i].get_position(),particle_list[j].get_position()).length();
            if (distance < 0.2f) //interection radius = 0.2
                particle_neighbours.push_back(j);
        }
    }
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
        neighbours(i,0);
        if (particle_neighbours.size() > 0)
        {
            for(unsigned long j = 0; j<particle_neighbours.size(); j++) //for each particle after the chosen particle in the list (pair)
            {
                unsigned long neigh = particle_neighbours[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);

                if (bv.length() != 0.0f)
                {
                    float q = bv.length()/0.2f;
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
            particle_neighbours.clear();
        }
    }
}



bool World::outside_tank(Particle P)
{
 auto distance = P.get_position().length();
 if (distance > _tank.radius -0.02f)
     return true;
 else
     return false;
}

void World::resolve_tank_collision()
{
    for(unsigned long i = 0; i<particle_list.size(); i++) //for each particle in particle_list
    {
        if (outside_tank(particle_list[i]) == true)
        {
            ngl::Vec3 pos = particle_list[i].get_position();
            pos.normalize();
            auto new_pos = pos * (_tank.radius -0.02f);
            particle_list[i].set_position(new_pos);
        }
    }
}



void World:: double_density_relaxation()
{
    for(unsigned long i = 0; i<particle_list.size(); i++)
    {
        float density =0;
        float near_density=0;
        neighbours(i,1);

        if (particle_neighbours.size() > 0)
        {
            for(unsigned long j = 0; j<particle_neighbours.size(); j++) //for each particle neighbour get density and near denisty
            {
                unsigned long neigh = particle_neighbours[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);
                float q = bv.length()/0.2f;
                density += (1-q)*(1-q);
                near_density += (1-q)*(1-q)*(1-q);
            }

            float pressure = 0.004f*(density-3.0f); //rest density = 3.0f & stifness = 0.004
//            std::cout << "my pressure " << pressure << std::endl;
            float near_pressure = 0.01f*near_density; //stifness near = 0.01
//            std::cout << "my near pressure " << near_pressure << std::endl;
            ngl::Vec3 dx;

            for(unsigned long j = 0; j<particle_neighbours.size(); j++) //for each particle neighbour apply displacements
            {
                unsigned long neigh = particle_neighbours[j];
                ngl::Vec3 bv = between_vector(particle_list[i],particle_list[neigh]);

                float q =0;
                auto length =bv.length();

                if (length != 0.0f)
                {
                    q = bv.length()/0.2f;
//                    std::cout << "q " << q << std::endl;
                    bv.normalize();
//                    std::cout << "bv " << bv << std::endl;
                }

                 ngl::Vec3 D = time_step*time_step*(pressure*(1-q) + near_pressure*(1-q)*(1-q))*bv;
//                 std::cout << "D " << D << std::endl;
                 particle_list[neigh].set_position(particle_list[neigh].get_position()+(D/2));
                 dx -= (D/2);
//                 std::cout << "dx " << dx << std::endl;
            }

            particle_list[i].set_position(particle_list[i].get_position()+dx);
        }
        particle_neighbours.clear();
    }
}

void World::add_deform_springs(unsigned long i)
{
    neighbours(i,0);
    if (particle_neighbours.size() > 0)
    {

        for(unsigned long j = 0; j<particle_neighbours.size(); j++) //for each particle neighbour
        {
            if (particle_list[i]._springs.count(static_cast<int>(j)) == 0) //no spring present
            {
                unsigned long neigh = particle_neighbours[j]; //index in particle_list
//                std::cout << "neighbour" << neigh <<std::endl;
                particle_list[i]._springs[static_cast<int>(neigh)] = 0.1f; //add spring length 0.1f
//                std::cout << "length 0 to 1 " << particle_list[i]._springs[1] << std::endl;
            }
        }

        for(std::map<int,float>::iterator it = particle_list[i]._springs.begin(); it !=particle_list[i]._springs.end(); it++) //iterate over spring map
        {
            ngl::Vec3 bv = between_vector(particle_list[i],particle_list[static_cast<unsigned long>(it->first)]);
            //std::cout << it->first << " The 2 parts of map" << it->second << std::endl;
            float d = 0.1f*it->second; //yield ratio =0.1
            float length = bv.length();
            //std::cout << "L  " << length << std::endl;
//            std::cout << "L + d " << it->second -d << std::endl;
            if (length > (it->second + d))
            {
                it->second += time_step * 0.3f * (length - it->second - d);   //alpha/plasticity constant =0.3f
            }

            if (length < (it->second - d))
            {
                it->second -= time_step * 0.3f * (it->second - d - length);
            }
//            std::cout << "Lij  " << it->second << std::endl;
        }
        particle_neighbours.clear();
    }
}

void World::remove_springs(unsigned long i)
{
   for(std::map<int,float>::iterator it = particle_list[i]._springs.begin(); it != particle_list[i]._springs.end(); it++)
   {
       int neigh = it->first;
       float dist = between_vector(particle_list[i],particle_list[static_cast<unsigned long>(neigh)]).length();
       if (dist >0.2f)
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
//            std::cout << "it first and it second  " << it->first << it->second << std::endl;
//            std::cout << "bv" << bv << std::endl;
            ngl::Vec3 D = time_step*time_step*0.3f*(1-(it->second / 0.2f))*(it->second - bv.length())*bv;  //kspring = 0.3f
//            std::cout << "D" << D/2.0f << std::endl;
            particle_list[i].set_position(particle_list[i].get_position()-(D/2.0f));
            particle_list[static_cast<unsigned long>(it->first)].set_position(particle_list[static_cast<unsigned long>(it->first)].get_position()+(D/2.0f));
//            std::cout << "posn 0" << particle_list[0].get_position() << std::endl;
        }
    }
}
