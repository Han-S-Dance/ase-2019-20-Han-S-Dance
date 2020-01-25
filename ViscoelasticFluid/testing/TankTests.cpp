#include "Tank.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(Tank,userctor)
{
    Tank T(9.6f);
    EXPECT_EQ(T.radius,9.6f);
}
