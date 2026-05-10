#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP
#include <glm/glm.hpp> // High-performance math library

struct Particle {
    glm::vec2 position;
    glm::vec2 velocity;
    float mass;
    float radius;
    bool isStatic; // For ground or walls
};

class PhysicsWorld {
public:
    void addParticle(Particle p);
    void update(float dt);
    const std::vector<Particle>& getParticles() const;

private:
    std::vector<Particle> m_particles;
    glm::vec2 m_gravity = {0.0f, -9.81f};
};

/**
 * @brief Structure to hold the physical state of an object at any given time.
 */
struct SimulationState {
    double time;
    double position;
    double velocity;
};

/**
 * @brief A simple 1D Physics Engine using Semi-Implicit Euler Integration.
 */
class PhysicsEngine {
public:
    /**
     * @param initial_pos Starting height.
     * @param initial_vel Starting velocity (positive is up).
     * @param gravity Acceleration constant (default Earth gravity).
     * @param bounciness Energy retained after hitting the ground (0.0 to 1.0).
     */
    PhysicsEngine(double initial_pos, double initial_vel, double gravity = -9.81, double bounciness = 0.7);

    /**
     * @brief Updates the physics state based on elapsed time.
     * @param dt Delta time (time elapsed since last frame).
     */
    void step(double dt);

    /**
     * @brief Returns true if the object is above the ground or still has significant velocity.
     */
    bool isFalling() const;

    /**
     * @brief Returns the current state (time, y-pos, velocity).
     */
    SimulationState getState() const;

    /**
     * @brief Resets the object to a specific height (useful for interactive apps).
     */
    void reset(double position);

private:
    double m_position;
    double m_velocity;
    double m_acceleration;
    double m_time;
    double m_bounciness;
    const double m_groundLevel = -0.9; // Matches the bottom of the OpenGL NDC
};

#endif
