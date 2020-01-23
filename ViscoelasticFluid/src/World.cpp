#include "World.h"
#include <iostream>
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <Particle.h>
#include <ngl/Random.h>


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

const float time_step = 0.0333333f;
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

void World::neighbours(unsigned long i, unsigned long m_flag = 0) //flag = 0 lists all neighbours after the particle in particle_list & flag = 1 list all neighbours
{

    unsigned long start =0;
    if (m_flag == 0)
    {
        start=i;
    }

    ngl::Vec3 postn = particle_list[i].get_position();
    for(unsigned long j =start; j<particle_list.size() ; ++j)
    {
        if (i ==j)
            continue;
        else
        {
            float distance = (postn - particle_list[j].get_position()).length();
            if (distance < 0.2f) //interection radius = 0.2
                particle_neighbours.push_back(j);
        }
    }

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
                ngl::Vec3 dist = (particle_list[neigh].get_position() - particle_list[i].get_position());
                //std::cout << "my dist " << dist << std::endl;
                if (particle_list[neigh].get_position() != particle_list[i].get_position())
                {
                    float q = dist.length()/0.2f;
                    //std::cout << "dist_length " << q << std::endl;
                    dist.normalize();
                    //std::cout << "my normal dist " << dist << std::endl;
                    float u = (particle_list[i].get_velocity() - particle_list[neigh].get_velocity()).dot(dist);
                    //std::cout << "my u " << u << std::endl;

                    if (u > 0)
                    {
                        ngl::Vec3 I = time_step*(1.0f-q)*(0.2f*u + 0.1f*u*u)*dist; ///time step = 2 //sigma=0.2 //beta= 0.1
                        //std::cout << "my I " << I << std::endl;
                        particle_list[i].set_velocity(particle_list[i].get_velocity()-(I/2));
                        particle_list[neigh].set_velocity(particle_list[neigh].get_velocity()+(I/2));
                    }
                }
            }
            particle_neighbours.clear();
        }
    }
}
