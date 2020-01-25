#include "World.h"
#include <gtest/gtest.h>
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <Particle.h>

using namespace ::testing;
// for more details on gtest see here https://github.com/google/googletest/blob/master/googletest/docs/primer.md
// my lecture https://nccastaff.bournemouth.ac.uk/jmacey/PP/slides/testing/slides.html#/

TEST(World, defaultctor)
{
    World w;
    EXPECT_EQ(w.particle_list.size(), 0);
}

TEST(World, particle_generator) //might need change this depending on how particles created.
{
    World w(10,ngl::Vec3());;
    //w.generate_particles(10,ngl::Vec3());
    EXPECT_EQ(w.particle_list.size(),10);
}



TEST(World, getvelocity)
{
    World w(10,ngl::Vec3());
    //w.generate_particles(10,ngl::Vec3());
    for (unsigned long i=0 ; i<10 ; i++ )
        w.particle_list[i].set_velocity(ngl::Vec3(0.0f,1.0f,2.0f) );
    for (unsigned long i=0 ; i<10 ; i++ )
        EXPECT_EQ(w.particle_list[i].get_velocity(),ngl::Vec3(0.0f,1.0f,2.0f));
}


//TEST(World, gravity)
//{
//    World w(10,ngl::Vec3());
//    //w.generate_particles(10,ngl::Vec3());
//    for (unsigned long i=0 ; i<10 ; i++ )
//        w.particle_list[i].set_velocity(ngl::Vec3(10.0f,10.0f,10.0f));
//    w.apply_gravity();
//    for (unsigned long i=0 ; i<10 ; i++ )
//        EXPECT_EQ(w.particle_list[i].get_velocity(),ngl::Vec3(10.0f,9.67333f,10.0f));
//}

//TEST(World, position_update)
//{
//    World w(10,ngl::Vec3());
//    //w.generate_particles(10,ngl::Vec3());
//    for (unsigned long i=0 ; i<10 ; i++ )
//    {
//        w.particle_list[i].set_position(ngl::Vec3(10.0f,10.0f,10.0f));
//        w.particle_list[i].set_velocity(ngl::Vec3(1.0f,-1.0f,0.0f));
//    }
//    w.update_position();
//    for (unsigned long i=0 ; i<10 ; i++ )
//    {
//        EXPECT_EQ(w.particle_list[i].get_position(),ngl::Vec3(10.0333f,9.96667f,10.0f));
//        EXPECT_EQ(w.particle_list[i].get_lastposition(),ngl::Vec3(10.0f,10.0f,10.0f));
//    }
//}

TEST(World, velocity_update)
{
    World w(10,ngl::Vec3());
    //w.generate_particles(10,ngl::Vec3());
    for (unsigned long i=0 ; i<10 ; i++ )
    {
        w.particle_list[i].set_position(ngl::Vec3(10.0f,10.0f,10.0f));
        w.particle_list[i].set_velocity(ngl::Vec3(1.0f,-1.0f,0.0f));
    }
    w.update_position();
    w.predict_velocity();
    for (unsigned long i=0 ; i<10 ; i++ )
    {
        EXPECT_EQ(w.particle_list[i].get_velocity(),ngl::Vec3(1.0f,-1.0f,0.0f));
    }
}

TEST(World, neighbour_none)
{
    World w(1,ngl::Vec3());
    w.neighbours(0,1);
    EXPECT_TRUE(w.particle_neighbours.empty());
}

TEST(World, neighbours)
{
    World w(11,ngl::Vec3());
    for(unsigned long i = 0; i<w.particle_list.size(); i++) //for each particle in particle_list
    {
        w.particle_list[i].set_position(ngl::Vec3());
    }
    w.neighbours(6,1);
    EXPECT_EQ(w.particle_neighbours.size(),10);
    EXPECT_EQ(w.particle_neighbours[2],2.0f);

}

TEST(World, edge_neighbour)
{
    World w(2,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(0.14f,-0.1f,0.1f));
    w.particle_list[1].set_position(ngl::Vec3());
    w.neighbours(0,1);
    EXPECT_EQ(w.particle_neighbours.size(),1);

}

TEST(World, edge_non_neighbour)
{
    World w(2,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(0.15f,-0.1f,0.1f));
    w.particle_list[1].set_position(ngl::Vec3());
    w.neighbours(0,1);
    EXPECT_EQ(w.particle_neighbours.size(),0);
}

TEST(World, after_neighbour)
{
    World w(11,ngl::Vec3());
    for(unsigned long i = 0; i<w.particle_list.size(); i++) //for each particle in particle_list
    {
        w.particle_list[i].set_position(ngl::Vec3());
    }
    w.neighbours(6,0);
    EXPECT_EQ(w.particle_neighbours.size(),4);
}

TEST(World, clear_neighbour_list)
{
    World w(10,ngl::Vec3());
    EXPECT_EQ(w.particle_neighbours.size(),0);
    w.neighbours(6,0);
    w.particle_neighbours.clear();
    EXPECT_EQ(w.particle_neighbours.size(),0);
}


TEST(World, visocisty_one)
{
    World w(1,ngl::Vec3());
    w.apply_viscosity();
    EXPECT_EQ(w.particle_list[0].get_velocity(),ngl::Vec3(0.0f,0.0f,0.0f));

}

TEST(World, between_vector)
{
    World w(2,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(-0.1f,0.0f,0.0f));
    w.particle_list[1].set_position(ngl::Vec3(0.0f,0.0f,0.0f));
    ngl::Vec3 bv = w.between_vector(w.particle_list[0],w.particle_list[1]);
    EXPECT_EQ(bv,ngl::Vec3(0.1f,0.0f,0.0f));
}



TEST(World, viscocity)
{
    World w(2,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(-0.1f,0.0f,0.0f));
    w.particle_list[0].set_velocity(ngl::Vec3(1.0f,1.0f,1.0f));
    w.particle_list[1].set_position(ngl::Vec3(0.0f,0.0f,0.0f));
    w.apply_viscosity();
    EXPECT_EQ(w.particle_list[0].get_velocity(),ngl::Vec3(0.9975f,1.0f,1.0f));
    EXPECT_EQ(w.particle_list[1].get_velocity(),ngl::Vec3(0.0025f,0.0f,0.0f));
}

TEST(World, no_viscocity)
{
    World w(2,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(0.1f,0.0f,0.0f));
    w.particle_list[0].set_velocity(ngl::Vec3(1.0f,1.0f,1.0f));
    w.particle_list[0].set_position(ngl::Vec3());
    w.apply_viscosity();
    EXPECT_EQ(w.particle_list[0].get_velocity(),ngl::Vec3(1.0f,1.0f,1.0f));
    EXPECT_EQ(w.particle_list[1].get_velocity(),ngl::Vec3(0.0f,0.0f,0.0f));
}

TEST(World, viscocity_multiple)
{
    World w(10,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(-0.1f,0.0f,0.0f));
    w.particle_list[0].set_velocity(ngl::Vec3(1.0f,1.0f,1.0f));
    w.particle_list[1].set_position(ngl::Vec3());
    w.particle_list[2].set_position(ngl::Vec3(0.15f,0.0f,0.0f));
    w.particle_list[2].set_velocity(ngl::Vec3(0.0f,-1.0f,0.0f));
    w.apply_viscosity();
    EXPECT_EQ(w.particle_list[0].get_velocity(),ngl::Vec3(0.9975f,1.0f,1.0f));
    EXPECT_EQ(w.particle_list[1].get_velocity(),ngl::Vec3(0.00249791f,0.0f,0.0f));
}

TEST(World, outisde_tank)
{
    World w;
    Particle p;
    p.set_position(ngl::Vec3(6.0f,-2.0f,-7.1f));
    EXPECT_EQ(w.outside_tank(p),true);
}

TEST(World, inside_tank)
{
    World w;
    Particle p;
    p.set_position(ngl::Vec3(6.0f,-1.7f,7.1f));
    EXPECT_EQ(w.outside_tank(p),false);
}

TEST(World, tank_border)
{
    World w;
    Particle p;
    p.set_position(ngl::Vec3(9.48f,0.0f,0.0f));
    EXPECT_EQ(w.outside_tank(p),false);
}

TEST(World, update_tank_collision)
{
    World w(1,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(-10.0f,0.0f,0.0f));
    EXPECT_EQ(w.outside_tank(w.particle_list[0]),true);
    w.resolve_tank_collision();
    EXPECT_EQ(w.particle_list[0].get_position(),ngl::Vec3(-9.48f,0.0f,0.0f));
    EXPECT_EQ(w.outside_tank(w.particle_list[0]),false);
}

TEST(World, double_denisty)
{
    World w(10,ngl::Vec3());
    for(unsigned long i = 0; i<w.particle_list.size(); i++) //for each particle in particle_list
    {
        w.particle_list[i].set_position(ngl::Vec3(1.0f + i*0.001f, 0.0f, 0.0f));
    }
    w.double_density_relaxation();
    EXPECT_EQ(w.particle_list[0].get_position(),ngl::Vec3(1.0f,1.0f,1.0f));
}
