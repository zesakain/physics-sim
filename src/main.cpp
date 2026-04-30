#include <iostream>
#include <iomanip>
#include "PhysicsEngine.hpp"

int main() {
    // Configuration
    const double dt = 0.01;
    PhysicsEngine engine(100.0, 0.0);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Starting Simulation..." << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    while (engine.isFalling()) {
        engine.step(dt);
        SimulationState state = engine.getState();

        std::cout << "t: " << state.time 
                  << " s | y: " << state.position 
                  << " m | v: " << state.velocity << " m/s" << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Impact reached at t = " << engine.getState().time << " seconds" << std::endl;

    return 0;
}