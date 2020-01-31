# Han Dance ASE Assignment
 
## Design Document
 
I will be implementing a Particle-based Viscoelastic Fluid Simulation (Clavet _et al_. 2005), briefly mentioned in the first page of my CGI Techniques report. The simulation will be the final deliverable of this project, where the user can modify parameters for different viscoelastic effects.
 
The implementation method avoids explicit force integration by using a prediction-relaxation approach. Particles are moved according to their velocities and then their positions are relaxed, subject to positional constraints. At the end of the timestep, velocities are recomputed by subtracting previous positions from relaxed position.

The main simulation steps of this algorithm are as follows:

1. Update particle velocities according to gravity and viscosity.

2. Save the previous positions and move the particles according to their velocities.

3. Create and destory springs and modify their rest lengths and apply spring forces as particle displacements.

4. Volume conservation, anti-clustering, and surface tension are then enforced.

5. Collisions between particles and bodies are resolved.

6. Velocity is updated using previous position.

7. Repeat these steps for a fixed time.
 
The initial design of this system is:
 
**Class:** Particle
The purpose of this class is to generate a particle. It has four main attributes, position (ngl::Vec3), previous_position (ngl::Vec3), velocity (ngl::Vec3) and springs (std::map). These are the four attributes needed in the calculations of the particle system. Setter and getter functions are used to access private members.
 
**Class:** World
This is the biggest class and the purpose is to resolve all calculations in the world space. It has two mains attributes Particles (std::vector) that store the particle information a Tank that holds the particles and a spatial_map (std::map)
The main functions of tank are detailed below.

 
_**function:**_  update_map
Updates the spatial hash map by iterating over the particles and creating bins and storing particles in them. 
 
 
_**function:**_ : apply_gravity
Applies the gravitational force to each of the particles, changing their velocity.
 
 
_**function:**_  apply_viscosity
Applies viscosity forces between neighbouring particles (using class Neighbour), and changes their position based on relative velocity.
 

_**function:**_ : update_position
Changes the position of a particle based on the current position, time and velocity and saves position to previous_position
 
 
_**function:**_ : predict_velocity
Updates the particles velocity using the old and new postions.
 
 
_**function:**_ : spring_displacement
If springs are present between 2 particles each of the particle's position will be displaced
 
 
_**function:**_ : double_density_relaxation
Displaces particles in the world based on how clunmped together they are.
 
 
_**function:**_ : resolve_tank_collision
If particles are predicted to be outside the tank this function moves them back in and applies an impulse to them.
 
 

The classes link like this. Particle and Tank are both included in World. World generates the particles and a single tank around them. World applies all the behaviours. NGLScene uses worls to create the simulaton that is viewed on the screen. MainWindow.h applies this into a user interface.

**How operate the programme:**
1. ./ViscoeladticFluid in the terminal whilst in the ViscoelasticFluid folder or run in qtcreator.

2. Input the number of particles, spread (between 0 and 1) and if a random initial velocity is wanted for the particles.

3. Press Generate.

4. During the simulation of the particles different characterisitics can be toggles on and off. These include: viscosity, springs and relaxation. 

5. Parameters that affect these characteristics can also be changed to arise in different particle motion, alongisde the interaction radius between particles and gravity.

6. Stop will pause the timer event.

7. Generate button will create a new simulation with the specified generation parameters.