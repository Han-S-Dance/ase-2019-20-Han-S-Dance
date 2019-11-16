﻿
#include "Particle.h"
#include <gtest/gtest.h>
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
using namespace ::testing;
// for more details on gtest see here https://github.com/google/googletest/blob/master/googletest/docs/primer.md
// my lecture https://nccastaff.bournemouth.ac.uk/jmacey/PP/slides/testing/slides.html#/

TEST(Particle, defaultctor)
{
    Particle p;
    EXPECT_EQ(p.position(),ngl::Vec3());
    EXPECT_EQ(p.lastposition(),ngl::Vec3());
    EXPECT_EQ(p.velocity(),ngl::Vec3());

}

TEST(Particle, userctor)
{
    Particle p(ngl::Vec3(10,20,30),ngl::Vec3(40,50,60),ngl::Vec3(70,80,90));
    EXPECT_EQ(p.position(),ngl::Vec3(10,20,30));
    EXPECT_EQ(p.lastposition(),ngl::Vec3(40,50,60));
    EXPECT_EQ(p.velocity(),ngl::Vec3(70,80,90));


}

TEST(Particle, setposition)
{
    Particle p;
    p.set_position(ngl::Vec3(10,20,30));
    EXPECT_EQ(p.get_position(),ngl::Vec3(10,20,30));
}


TEST(Particle, lastposition)
{
     Particle p;
     p.set_position(ngl::Vec3(10,20,30));
     p.update_lastposition();
     EXPECT_EQ(p.get_lastposition(),ngl::Vec3(10,20,30));
}


TEST(Particle, setvelocity)
{
    Particle p;
    p.set_velocity(ngl::Vec3(10,20,30));
    EXPECT_EQ(p.get_velocity(),ngl::Vec3(10,20,30));

}

TEST(Particle, compare)
{
    Particle p(ngl::Vec3(10,20,30),ngl::Vec3(40,50,60),ngl::Vec3(70,80,90));
    Particle q(ngl::Vec3(10,20,30),ngl::Vec3(40,50,60),ngl::Vec3(70,80,90));
    EXPECT_EQ(p,q);

}