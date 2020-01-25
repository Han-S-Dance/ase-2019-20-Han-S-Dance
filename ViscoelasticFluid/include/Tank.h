#pragma once
//bounding box for the particles to live in
#include <ngl/Vec3.h>

class Tank
{
  public:
    Tank(float _radius);
    Tank()=default;
    ~Tank() noexcept =default;
    Tank(const Tank &)=default;
    Tank & operator=(const Tank &)=default;
    Tank(Tank &&)=default;
    Tank & operator=(Tank &&)=default;

    float radius;
};


