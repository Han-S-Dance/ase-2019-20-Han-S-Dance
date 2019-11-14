# Han Dance ASE Assignment
 
## Design Document
 
I will be implementing a Particle-based Viscoelastic Fluid Simulation (Clavet _et al_. 2005), briefly mentioned in the first page of my CGI Techniques report. The simulation will be the final deliverable of this project, where the user can modify parameters for different viscoelastic effects.
 
The main simulation steps of this algorithm are as follows:
1.Update the particle's position based on velocity.
2.Compute various forces for each particle and modify the position.
3.Modify the velocity based on these forces.
repeat these steps for a fixed time.
 
The initial design of this system is:
 
**Class:** Particle
The purpose of this class is to generate a particle. It has four main attributes, position (ngl::Vec3), previous_position (ngl::Vec3) and velocity (ngl::Vec3). These are the four attributes needed in the calculations of the particle system. Setter and getter functions are used to access private members.
 
 
**Class:** Spring
The purpose of this class is to generate a spring which applies forces between neighbouring particles. Spring has three main attributes: particle_one (pointer), particle_two (pointer) and rest_length (float).
 
**Class:** Neighbour
The purpose of this class is to generate a list of neighbours for a particle. The main attribute is particle_neighbours (std::vector of pointers).
 
_**function:**_  get_neighbours
Searches (within a specified area) to find and return the pointers to all neighbouring particles within interaction radius h and adds these to the vector.
 
 
**Class:** Collision
The purpose of this class is to detect any collisions between particles and other objects. The main attribute is collison_position(ngl::Vec3) used to update the particle's position.
 
_**function:**_  detect_collision
will take a particle and sphere and test whether they have collided, if true will return the collision position.
 
 
**Class:** World
This is the biggest class and the purpose is to resolve all calculations in the world space. It has two mains attributes Particles (std::vector) that store the particle information and Springs (std::vector) that store the information of all springs.
 
 
_**function:**_ create_particles
Will generate multiple particles (using class Particles) and add them to the vector.
 
 
_**function:**_  indexing_grid
Creates a 3D grid with cube size equal to the interaction radius h. Will allow for a fast efficient neighbour search as particles will only have to search in 28 neighbouring cubes. 
 
 
_**function:**_ : gravity
Applies the gravitational force to each of the particles, changing their velocity.
 
 
_**function:**_  viscosity
Applies viscosity forces between neighbouring particles (using class Neighbour), and changes their position based on relative velocity.
 
 
_**function:**_ : update_previous_position
Moves the position of a particle to the previous position.
 
 
_**function:**_ : update_position
Changes the position of a particle based on the current position, time and velocity.
 
 
_**function:**_ : create_spring
Checks the distance between two neighbouring particles (using class Neighbour) and creates a spring within interaction radius h by appending them to Springs.
 
 
_**function:**_ : delete_spring
checks the distance between two neighbouring particles (using class Neighbour) and deletes a spring that is not within interaction radius by deleting them from Springs.
 
 
_**function:**_ : change_spring_rest_lengths
Changes the rest length of any existing springs and updates these in Springs.
 
 
_**function:**_ : spring_dispalcement
If springs are present between 2 particles each of the particle's position will be displaced. This is implemented by looking at Springs and displacing particles accordingly.
 
 
_**function:**_  attract_and_repel
Used to implement a double density relaxation algorithm which defines the attraction and repulsion between fluid particles. This changes the position of each particle in the pair (using class Neighbour).
 
 
_**function:**_ : resolve_collision
Changes particle position based on any detected collisions (using class Collision).
 
 
_**function:**_ : update_velocty
Updates the velocity using position, previous_position and velocity.
 
 
Implementation of additional classes and changes to current classes will most likely be made as I progress through the project.

