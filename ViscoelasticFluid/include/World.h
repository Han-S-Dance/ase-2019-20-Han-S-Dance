/// \brief encapsulates the simulation world
/// \author Han Dance
/// \version 2.0
/// \date 30/1/19 Updated layout
/// Revision History :
/// Initial Version 10/11/19


#ifndef World_H
#define World_H
#include <Particle.h>
#include <Tank.h>
#include <tuple>

class World
{
  public:
    World(unsigned int _numParticles, float _spread, bool _randVelocity);
    World()=default;
    ~World() noexcept =default;

    std::vector<Particle> particle_list;
    Tank _tank;
    std::map <std::tuple<int,int,int>,std::vector<std::size_t>> _spatial_map;

    void update_map();
    void apply_gravity();
    void apply_viscosity();
    void update_position();
    void predict_velocity();
    void spring_displacements();
    void double_density_relaxation();
    void resolve_tank_collision();


    void setFluidity(double _f);
    void setPlasticity(double _p);
    void setElasticity(double _e);
    void setDensity(double _d);
    void setPressure(double _p);
    void setInteractionRadius(double _i);
    void scaleGravity(double _g);

    ngl::Vec3 between_vector(Particle,Particle);

    void add_deform_springs(std::size_t);
    void remove_springs(std::size_t);

    bool outside_tank(Particle);
    ngl::Vec3 intersection_point(Particle);

    std::vector<std::size_t> map_neighbours(std::size_t i);
    std::vector<std::size_t> neighbours(std::size_t i,std::size_t _flag);

    std::tuple<int,int,int> hash_function(ngl::Vec3 _position);

    float m_gravityscale;

private:

    float m_fluidity;
    float m_plasticity;
    float m_elasticity;
    float m_density;
    float m_pressure;
    float m_interaction_radius;

    float cube_size;

    float inward_radial_veloctiy(Particle,Particle,ngl::Vec3);
    ngl::Vec3 linear_quadratic_impulses(float,float,ngl::Vec3);

    void adjust_springs();


};

#endif
