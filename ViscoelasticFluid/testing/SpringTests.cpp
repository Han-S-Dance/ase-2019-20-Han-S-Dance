#include "Spring.h"
#include <gtest/gtest.h>
#include <ngl/NGLStream.h>
#include <ngl/Vec3.h>
#include <Particle.h>

using namespace ::testing;
// for more details on gtest see here https://github.com/google/googletest/blob/master/googletest/docs/primer.md
// my lecture https://nccastaff.bournemouth.ac.uk/jmacey/PP/slides/testing/slides.html#/


//Userctor
//TEST(Spring, userCtor)
//{
//    Particle p;
//    Particle q;
//    Spring s(&p,&q,10);
//    EXPECT_EQ(*s.particle_one(),p);
//    EXPECT_EQ(*s.particle_one(),q);
//    EXPECT_EQ(s.rest_length(),10);

//}



//TEST(Spring, setrestlength)
//{

//    Particle p;
//    Particle q;
//    Spring s(&p,&q,0);

//    s.set_spring_rest_length(10);
//    EXPECT_EQ(s.get_spring_rest_length(),10);
//}
