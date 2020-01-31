/// \brief encapsulates a sphere
/// \author Jonathan Macey
/// \version 2.0
/// \date 30/1/20 Updated comments
/// Revision History :
/// Initial Version 20/1/20

#pragma once

class Tank
{
  public:
    Tank(float _radius);
    Tank()=default;
    ~Tank() noexcept =default;

    float radius;
};


