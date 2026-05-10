#include "PhysicsEngine.hpp"

PhysicsEngine::PhysicsEngine(double initial_pos, double initial_vel, double gravity, double bounciness)
    : m_position(initial_pos),
      m_velocity(initial_vel),
      m_acceleration(gravity),
      m_time(0.0),
      m_bounciness(bounciness) {}

void PhysicsEngine::step(double dt) {
    // 1. Update velocity (v = v + a * dt)
    m_velocity += m_acceleration * dt;

    // 2. Update position (y = y + v * dt)
    m_position += m_velocity * dt;

    // 3. Collision Detection with Ground
    // If the object goes below ground level, make it bounce.
    if (m_position <= m_groundLevel) {
        m_position = m_groundLevel;      // Snap to ground to prevent sinking
        m_velocity *= -m_bounciness;     // Reverse velocity and apply friction/energy loss

        // Stop tiny micro-bounces (stability check)
        if (m_velocity < 0.1 && m_velocity > -0.1) {
            m_velocity = 0;
        }
    }

    m_time += dt;
}

bool PhysicsEngine::isFalling() const {
    // Object is "active" if it's above ground or still moving
    return m_position > m_groundLevel || m_velocity != 0;
}

SimulationState PhysicsEngine::getState() const {
    return {m_time, m_position, m_velocity};
}

void PhysicsEngine::reset(double position) {
    m_position = position;
    m_velocity = 0.0;
    m_time = 0.0;
}
