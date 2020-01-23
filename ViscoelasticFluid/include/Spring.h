#ifndef Spring_H
#define Spring_H


#include <Particle.h>

class Spring
{
  public :
    Spring(Particle* _particle_one, Particle* _particle_two, float _rest_length);
    Spring() = default;
    ~Spring() noexcept =default;
    Spring(const Spring &)=default;
    Spring & operator=(const Spring &)=default;
    Spring(Spring &&)=default;
    Spring & operator=(Spring &&)=default;
    Particle* particle_one();
    Particle* particle_two();
    float rest_length();


    void set_spring_rest_length(float);
    float get_spring_rest_length();

  private:
    float m_rest_length=0;
    Particle* m_particle_one = nullptr;
    Particle* m_particle_two = nullptr;

};

#endif
