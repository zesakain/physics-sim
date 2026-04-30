#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <vector>

struct SimulationState {
    double time;
    double position;
    double velocity;
};

class PhysicsEngine {
public:
    // Constructor to initialize physical constants
    PhysicsEngine(double initial_pos, double initial_vel, double gravity = -9.81);

    // Updates the state of the object based on time step dt
    void step(double dt);

    // Check if the object has hit the ground
    bool isFalling() const;

    // Getters for the current state
    SimulationState getState() const;

private:
    double m_position;
    double m_velocity;
    double m_acceleration;
    double m_time;
};

#endif