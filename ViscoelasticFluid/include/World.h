#ifndef World_H
#define World_H
#include <Particle.h>
#include <Tank.h>
#include <array>
#include <ngl/Random.h>


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
   // std::vector<unsigned long> particle_neighbours; //get rid of this!
    const float interaction_radius = 0.2f;

    Tank _tank = Tank(1.2f);
    std::vector<std::vector<int>> _spatial_map;

    int hash_function(float _value, float _min_value, float _division_size);
    void update_map();

    float cube_size = 0.4f;
    float minx;
    float miny;
    float minz;
    float x_divisions;
    float y_divisions;

    std::vector<int> map_neighbours(unsigned long i);
    std::vector<unsigned long> neighbours(unsigned long p,unsigned long _flag);

    ngl::Vec3 between_vector(Particle,Particle);

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
    ngl::Vec3 intersection_point(Particle);
    void resolve_tank_collision();

};

#endif

