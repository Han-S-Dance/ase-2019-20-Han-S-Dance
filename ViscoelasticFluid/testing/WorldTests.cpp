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

TEST(World, userctor)
{
    World w(10,ngl::Vec3());
    EXPECT_EQ(w.particle_list.size(),10);
    for (unsigned long i=0 ; i<10 ; i++ )
        EXPECT_NE(w.particle_list[i].get_position(),ngl::Vec3());
}


TEST(World, hash_function)
{
    World w;
    EXPECT_EQ(w.hash_function(-9.5f, -9.5f ,0.2f),0);
    EXPECT_EQ(w.hash_function(-9.3f, -9.5f ,0.2f),1);
    EXPECT_EQ(w.hash_function(-8.91f,-9.5f ,0.2f),2);
    EXPECT_EQ(w.hash_function(-8.9f,-9.5f ,0.2f),3);
    EXPECT_EQ(w.hash_function(-8.7f,-9.5f ,0.2f),4);
    EXPECT_EQ(w.hash_function(9.5f,-9.5f ,0.2f),95);
}


TEST(World, map_size)
{
    World w(3,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(9.0f,1.0f,2.0f));
    w.particle_list[1].set_position(ngl::Vec3(2.1f,2.5f,2.5f));
    w.particle_list[2].set_position(ngl::Vec3(2.2f,2.6f,2.6f));
    w.update_map();
    EXPECT_EQ(w._spatial_map.size(),112);
    EXPECT_EQ(w._spatial_map[13].size(),1);
    EXPECT_EQ(w._spatial_map[98].size(),2);
}


TEST(World, clearmap)
{
    World w(2,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(9.5f,9.5f,9.5f));
    w.particle_list[1].set_position(ngl::Vec3(0.5f,1.5f,2.5f));
    w.update_map();
    EXPECT_EQ(w._spatial_map[0].size(),1);
    w.update_map();
    EXPECT_EQ(w._spatial_map[0].size(),1);
}


TEST(World, updatemap)
{
    World w(3,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(9.0f,1.0f,2.0f));
    w.particle_list[1].set_position(ngl::Vec3(2.1f,2.5f,2.5f));
    w.particle_list[2].set_position(ngl::Vec3(2.2f,2.6f,2.6f));
    w.update_map();
    EXPECT_EQ(w._spatial_map.size(),112);
    EXPECT_EQ(w._spatial_map[13].size(),1);
    EXPECT_EQ(w._spatial_map[98].size(),2);
    w.particle_list[0].set_position(ngl::Vec3(1.1f,1.0f,2.0f));
    w.particle_list[1].set_position(ngl::Vec3(1.2f,0.9f,2.0f));
    w.particle_list[2].set_position(ngl::Vec3(1.6f,0.6f,2.45f));
    w.update_map();
    EXPECT_EQ(w._spatial_map.size(),2);
    EXPECT_EQ(w._spatial_map[0].size(),2);
    EXPECT_EQ(w._spatial_map[1].size(),1);
    w.particle_list[0].set_position(ngl::Vec3(9.0f,1.0f,2.0f));
    w.particle_list[1].set_position(ngl::Vec3(2.1f,2.5f,2.5f));
    w.particle_list[2].set_position(ngl::Vec3(2.2f,2.6f,2.6f));
    w.update_map();
    EXPECT_EQ(w._spatial_map.size(),112);
    EXPECT_EQ(w._spatial_map[13].size(),1);
    EXPECT_EQ(w._spatial_map[98].size(),2);
}


TEST(World, getvelocity)
{
    World w(10,ngl::Vec3());
    for (unsigned long i=0 ; i<10 ; i++ )
        w.particle_list[i].set_velocity(ngl::Vec3(0.0f,1.0f,2.0f) );
    for (unsigned long i=0 ; i<10 ; i++ )
        EXPECT_EQ(w.particle_list[i].get_velocity(),ngl::Vec3(0.0f,1.0f,2.0f));
}


TEST(World, gravity)
{
    World w(1,ngl::Vec3());
    w.apply_gravity();
    EXPECT_EQ(w.particle_list[0].get_velocity(),ngl::Vec3(0.0f,-0.32667f,0.0f));
}

TEST(World, position_update)
{
    World w(1,ngl::Vec3());
    w.apply_gravity();
    w.particle_list[0].set_position(ngl::Vec3());
    EXPECT_EQ(w.particle_list[0].get_velocity(),ngl::Vec3(0.0f,-0.32667f,0.0f));
    w.update_position();
    EXPECT_EQ(w.particle_list[0].get_position(),ngl::Vec3(0.0f,-0.010889f,0.0f));

}

TEST(World, velocity_update)
{
    World w(10,ngl::Vec3());
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

TEST(World, map_neighbour)
{
    World w(4,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(0.0f,0.0f,0.0f));
    w.particle_list[1].set_position(ngl::Vec3(0.1f,0.1f,0.1f));
    w.particle_list[2].set_position(ngl::Vec3(0.1f,0.2f,0.2f));
    w.particle_list[3].set_position(ngl::Vec3(0.5f,0.2f,0.2f));
    w.update_map();
    std::vector<int> cube_neighbours = w.map_neighbours(0);
    EXPECT_EQ(cube_neighbours.size(),3); //includes self
}

TEST(World, neighbours)
{
    World w(4,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(0.0f,0.0f,0.0f));
    w.particle_list[1].set_position(ngl::Vec3(0.1f,0.1f,0.1f));
    w.particle_list[2].set_position(ngl::Vec3(0.1f,0.2f,0.2f));
    w.particle_list[3].set_position(ngl::Vec3(0.5f,0.2f,0.2f));
    w.update_map();
    std::vector<unsigned long> Neighbours = w.neighbours(0,1);
    EXPECT_EQ(Neighbours.size(),1);
    Neighbours = w.neighbours(1,1);
    EXPECT_EQ(Neighbours.size(),2);
}

TEST(World, after_neighbours)
{
    World w(4,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(0.0f,0.0f,0.0f));
    w.particle_list[1].set_position(ngl::Vec3(0.1f,0.1f,0.1f));
    w.particle_list[2].set_position(ngl::Vec3(0.1f,0.2f,0.2f));
    w.particle_list[3].set_position(ngl::Vec3(0.5f,0.2f,0.2f));
    w.update_map();
    std::vector<unsigned long> Neighbours = w.neighbours(0,0);
    EXPECT_EQ(Neighbours.size(),1);
    std::vector<unsigned long> Neighbours_two = w.neighbours(1,0);
    EXPECT_EQ(Neighbours_two.size(),1);
}

TEST(World, visocisty_one)
{
    World w(1,ngl::Vec3());
    w.update_map();
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
    w.update_map();
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
    w.update_map();
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
    w.update_map();
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
    p.set_position(ngl::Vec3(9.5f,0.0f,0.0f));
    EXPECT_EQ(w.outside_tank(p),false);
}

TEST(World, collision_point)
{
    World w;
    Particle p;
    p.set_position(ngl::Vec3(-0.1f,0.0f,0.0f));
    p.update_lastposition();
    p.set_position(ngl::Vec3(1.0f,0.0f,0.0f));
    EXPECT_EQ(w.intersection_point(p),ngl::Vec3(9.5f,0.0f,0.0f));

}

TEST(World, collision_point_multiple)
{
    World w;
    Particle p;
    p.set_position(ngl::Vec3(-0.1f,0.1f,2.0f));
    p.update_lastposition();
    p.set_position(ngl::Vec3(-0.15f,-10.0f,2.5f));
    EXPECT_EQ(w.intersection_point(p),ngl::Vec3(-0.145916f,-9.17503f,2.45916f));
    EXPECT_FLOAT_EQ(w.intersection_point(p).length(),w._tank.radius);

}

TEST(World, update_tank_collision)
{
    World w(1,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3(-9.0f,0.0f,0.0f));
    w.particle_list[0].update_lastposition();
    w.particle_list[0].set_position(ngl::Vec3(-10.0f,0.0f,0.0f));
    EXPECT_EQ(w.outside_tank(w.particle_list[0]),true);
    w.resolve_tank_collision();
    EXPECT_EQ(w.particle_list[0].get_position(),ngl::Vec3(-9.0f,0.0f,0.0f));
    EXPECT_EQ(w.outside_tank(w.particle_list[0]),false);
}

TEST(World, double_denisty)
{
    World w(10,ngl::Vec3());
    for(unsigned long i = 0; i<w.particle_list.size(); i++) //for each particle in particle_list
    {
        w.particle_list[i].set_position(ngl::Vec3(1.0f + i*0.001f, 0.0f, 0.0f));
    }
    w.update_map();
    w.double_density_relaxation();
    EXPECT_NE(w.particle_list[0].get_position(),ngl::Vec3(1.0f,1.0f,1.0f));
}


TEST(World, remove_springs)
{
    World w(2,ngl::Vec3());
    w.particle_list[0].set_position(ngl::Vec3());
    w.particle_list[1].set_position(ngl::Vec3(0.1f,0.0f,0.0f));
    w.update_map();
    w.add_deform_springs(0);
    EXPECT_EQ(w.particle_list[0]._springs.size(),1);
    EXPECT_EQ(w.particle_list[1]._springs.size(),0);

    //remove spring
    w.particle_list[1].set_position(ngl::Vec3(2.01f,0.0f,0.0f));
    w.remove_springs(0);
    EXPECT_EQ(w.particle_list[0]._springs.size(),0);
}


TEST(World, springs)
{
    World w(100,ngl::Vec3());
    for(unsigned long i = 0; i<w.particle_list.size(); i++) //for each particle in particle_list
    {
        w.particle_list[i].set_position(ngl::Vec3(0.0f - i*0.001f, 0.001f, 0.0f));
    }
    w.update_map();
//    w.spring_displacements();
//    w.predict_velocity();
//    w.update_position();
//    EXPECT_NE(w.particle_list[50].get_position(),ngl::Vec3(0.005f,0.005f,0.0f));
}


//TEST(World, one_spring)
//{
//    World w(2,ngl::Vec3());
//    w.particle_list[0].set_position(ngl::Vec3());
//    w.particle_list[1].set_position(ngl::Vec3(0.05f,0.0f,0.0f));
//    w.spring_displacements();
//    EXPECT_EQ(w.particle_list[1].get_position(),ngl::Vec3(0.05f,0.0f,0.0f));
//}
