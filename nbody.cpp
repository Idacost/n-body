#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>

//Gravitational Constant
const double G = 6.67430e-11;

struct Particle {
    double mass;
    std::vector<double> position;
    std::vector<double> velocity;
    std::vector<double> force;
};

void resetForce(std::vector<Particle>& particles) {
    for (int i = 0; i < particles.size(); ++i) {
        auto& p = particles[i];
        p.force = {0.0, 0.0, 0.0};
    }
}

void calculateForce(std::vector<Particle>& particles) {
    for (int i = 0; i < particles.size(); i++) {
        for (int j = 0; j < particles.size(); j++) {
            //Skip self interaction
            if (i == j) continue; 

            double distanceX = particles[i].position[0] - particles[j].position[0];
            double distanceY = particles[i].position[1] - particles[j].position[1];
            double distanceZ = particles[i].position[2] - particles[j].position[2];

            //Calculate distance between particles
            double r = sqrt(distanceX * distanceX + distanceY * distanceY + distanceZ * distanceZ);
            if (r == 0) continue;

            //Calculate Force
            double forceCalc = G * ((particles[i].mass * particles[j].mass) / (r * r));

            double forceX = forceCalc * (distanceX / r);
            double forceY = forceCalc * (distanceY / r);
            double forceZ = forceCalc * (distanceZ / r);

            particles[i].force[0] += forceX;
            particles[i].force[1] += forceY;
            particles[i].force[2] += forceZ;

            particles[j].force[0] -= forceX;
            particles[j].force[1] -= forceY;
            particles[j].force[2] -= forceZ;
        }
    }
}

void updateVelocity(std::vector<Particle>& particles, double timeStep) {
    for (int i = 0; i < particles.size(); ++i) {
        auto& p = particles[i];

        // Update velocity based on force and mass
        p.velocity[0] += (p.force[0] / p.mass) * timeStep;
        p.velocity[1] += (p.force[1] / p.mass) * timeStep;
        p.velocity[2] += (p.force[2] / p.mass) * timeStep;
    }
}

void updatePosition(std::vector<Particle>& particles, double timeStep) {
    for (int i = 0; i < particles.size(); ++i) {
        auto& p = particles[i];

        // Update position based on velocity
        p.position[0] += p.velocity[0] * timeStep;
        p.position[1] += p.velocity[1] * timeStep;
        p.position[2] += p.velocity[2] * timeStep;
    }
}

void predefinedConfig(std::vector<Particle>& particles) {
    // Sun
    Particle sun;

    sun.mass = 1.989e30;
    sun.position = {0.0, 0.0, 0.0};
    sun.velocity = {0.0, 0.0, 0.0};
    sun.force = {0.0, 0.0, 0.0};
    particles.push_back(sun);

    // Earth
    Particle earth;
    earth.mass = 5.972e24;  // Earth's mass
    earth.position = {1.496e11, 0.0, 0.0};  // Earth's position (about 1 AU from the Sun)
    earth.velocity = {0.0, 29.78e3, 0.0};  // Earth's velocity in orbit
    particles.push_back(earth);

    // Moon
    Particle moon;
    moon.mass = 7.348e22;  // Moon's mass
    moon.position = {1.496e11 + 384400000, 0.0, 0.0};  // Moon's position
    moon.velocity = {0.0, 29.78e3 + 1.022e3, 0.0};  // Moon's velocity
    particles.push_back(moon);
};

void randomParticle(std::vector<Particle>& particles, int numParticles) {
    for (int i = 0; i < numParticles; i++) {
        Particle p;
        p.mass = rand() % 100 + 1;
        p.position = {static_cast<double>(rand() % 100 - 50), static_cast<double>(rand() % 100 - 50), static_cast<double>(rand() % 100 - 50)};
        p.velocity = {static_cast<double>(rand() % 10 - 5), static_cast<double>(rand() % 10 - 5), static_cast<double>(rand() % 10 - 5)};
        p.force = {0.0, 0.0, 0.0};
        particles.push_back(p);
    }
}

void outputToFile(const std::vector<Particle>& particles, std::ofstream& outFile) {
    outFile << particles.size() << "\t";  // Number of particles

    for (const auto& p : particles) {
        outFile << p.mass << "\t"
                << p.position[0] << "\t" << p.position[1] << "\t" << p.position[2] << "\t"
                << p.velocity[0] << "\t" << p.velocity[1] << "\t" << p.velocity[2] << "\t"
                << p.force[0] << "\t" << p.force[1] << "\t" << p.force[2] << "\t";
    }
    outFile << "\n";
}

int main() {
    int numParticles, numSteps, dumpFrequency;
    double timeStep;

    std::cout << "Enter number of particles: ";
    std::cin >> numParticles;
    std::cout << "Enter time step size: ";
    std::cin >> timeStep;
    std::cout << "Enter number of iterations: ";
    std::cin >> numSteps;
    std::cout << "Enter dump frequency: ";
    std::cin >> dumpFrequency;

    //Initialize random seed
    srand (time(0)); 

    std::vector<Particle> particles;
    randomParticle(particles, numParticles);

    std::ofstream outFile("nbody_output.txt");

    // Simulation loop
    for (int step = 0; step < numSteps; ++step) {
        // Reset the forces for each step
        resetForce(particles);

        // Calculate the forces between particles
        calculateForce(particles);

        // Update velocities based on forces and time step
        updateVelocity(particles, timeStep);

        // Update positions based on velocities and time step
        updatePosition(particles, timeStep);

        // Output particle data to file at the specified frequency
        if (step % dumpFrequency == 0) {
            outputToFile(particles, outFile);
        }
    }

    
    /*
    Console Output

    // Reset the forces
    resetForce(particles);

    // Calculate the forces between the particles
    calculateForce(particles);

    // Update velocities based on forces and time step
    updateVelocity(particles, timeStep);

    // Update positions based on velocities and time step
    updatePosition(particles, timeStep);


    for (int i = 0; i < particles.size(); ++i) {

        std::cout << "Particle " << i + 1 << " Mass: " << particles[i].mass << " kg\n";

        std::cout << "Particle " << i + 1 << " Position: ";
        for (int j = 0; j < 3; ++j) {
            std::cout << particles[i].position[j] << " ";
        }
        std::cout << "\n";

        std::cout << "Particle " << i + 1 << " Velocity: ";
        for (int j = 0; j < 3; ++j) {
            std::cout << particles[i].velocity[j] << " ";
        }
        std::cout << "\n";

    
        std::cout << "Particle " << i + 1 << " Force: ";
        for (int j = 0; j < 3; ++j) {
            std::cout << particles[i].force[j] << " ";
        }
        std::cout << "\n";
    }
    */

    outFile.close();

    std::cout << "Simulation output saved to 'nbody_output.txt'.\n";

    return 0;
};