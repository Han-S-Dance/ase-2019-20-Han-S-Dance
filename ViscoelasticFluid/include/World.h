#ifndef World_H
#define World_H
#include <Particle.h>

class World
{
  public:
    World(unsigned int _num_Worlds, ngl::Vec3 _posn);
    World()=default;
    ~World() noexcept =default;
    World(const World &)=default;
    World & operator=(const World &)=default;
    World(World &&)=default;
    World & operator=(World &&)=default;

    std::vector<Particle> particle_list;
    std::vector<unsigned long> particle_neighbours;

    void apply_gravity();
    void update_position();
    void predict_velocity();
    void apply_viscosity();
    void neighbours(unsigned long,unsigned long);

};

#endif

