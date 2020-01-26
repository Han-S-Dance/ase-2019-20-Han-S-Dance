#ifndef World_H
#define World_H
#include <Particle.h>
#include <Tank.h>

class World
{
  public:
    World(unsigned int _num_particles, ngl::Vec3 _posn);
    World()=default;
    ~World() noexcept =default;
    World(const World &)=default;
    World & operator=(const World &)=default;
    World(World &&)=default;
    World & operator=(World &&)=default;

    std::vector<Particle> particle_list;
    std::vector<unsigned long> particle_neighbours;

    Tank _tank = Tank(9.5f);

    ngl::Vec3 between_vector(Particle,Particle);
    void neighbours(unsigned long,unsigned long _flag);

    void apply_gravity();

    float inward_radial_veloctiy(Particle,Particle,ngl::Vec3);
    ngl::Vec3 linear_quadratic_impulses(float,float,ngl::Vec3);
    void apply_viscosity();

    void update_position();
    void predict_velocity();

    void add_deform_springs(unsigned long);
    void remove_springs(unsigned long);
    void adjust_springs();
    void spring_displacements();

    void double_density_relaxation();

    bool outside_tank(Particle);
    void resolve_tank_collision();

};

#endif

