#include "Particle.h"
#include <gtest/gtest.h>

using namespace ::testing;
// for more details on gtest see here https://github.com/google/googletest/blob/master/googletest/docs/primer.md
// my lecture https://nccastaff.bournemouth.ac.uk/jmacey/PP/slides/testing/slides.html#/

TEST(Particle, userctor)
{
    Particle p(ngl::Vec3(1.0f,-1.0f,0.2f),ngl::Vec3(2.2f,-6.7f,0.0f));
    EXPECT_EQ(p.get_position(),ngl::Vec3(1.0f,-1.0f,0.2f));
    EXPECT_EQ(p.get_velocity(),ngl::Vec3(2.2f,-6.7f,0.0f));
}


TEST(Particle, defaultctor)
{
    Particle p;
    EXPECT_EQ(p.get_position(),ngl::Vec3());
    EXPECT_EQ(p.get_lastposition(),ngl::Vec3());
    EXPECT_EQ(p.get_velocity(),ngl::Vec3());
    EXPECT_TRUE(p._springs.empty());

}


TEST(Particle, setposition)
{
    Particle p;
    p.set_position(ngl::Vec3(10,20,30));
    EXPECT_EQ(p.get_position(),ngl::Vec3(10,20,30));
    EXPECT_EQ(p.get_position()[0],10);
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

TEST(Particle, SetXYZposition)
{
    Particle p;
    p.setX_position(10.0f);
    p.setY_position(-12.2f);
    p.setZ_position(-0.1f);
    EXPECT_EQ(p.get_position(),ngl::Vec3(10.0f,-12.2f,-0.1f));
}

TEST(Particle , spring)
{
    Particle p;
    p._springs[6] = 0.9f;
    EXPECT_EQ(p._springs[6], 0.9f);
    p._springs[6] += 0.2f;
    EXPECT_EQ(p._springs[6], 1.1f);
}
