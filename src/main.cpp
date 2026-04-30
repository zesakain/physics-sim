#include <iostream>
using namespace std;

int main() {
    double position = 100.0; // meter
    double velocity = 0.0;
    double acceleration = -9.81; // gravitasi
    double dt = 0.01; // time step
    double time = 0.0;

    while (position > 0) {
        velocity += acceleration * dt;
        position += velocity * dt;

        time += dt;

        cout << "t: " << time 
             << " | y: " << position 
             << " | v: " << velocity << endl;
    }

    cout << "Touch t = " << time << " Second" << endl;
    return 0;
}
