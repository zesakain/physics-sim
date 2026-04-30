#include "PhysicsEngine.hpp"

PhysicsEngine::PhysicsEngine(double initial_pos, double initial_vel, double gravity)
    : m_position(initial_pos), m_velocity(initial_vel), m_acceleration(gravity), m_time(0.0) {}

void PhysicsEngine::step(double dt) {
    // Semi-implicit Euler integration (more stable than standard Euler)
    m_velocity += m_acceleration * dt;
    m_position += m_velocity * dt;
    m_time += dt;
}

bool PhysicsEngine::isFalling() const {
    return m_position > 0.0;
}

SimulationState PhysicsEngine::getState() const {
    return {m_time, m_position, m_velocity};
}