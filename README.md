# N-body Gravitational Simulation

This C++ project simulates gravitational interactions between particles using the N-body problem.

## Compilation

1. **Compile the code**:

    Using `g++`:

    ```bash
    g++ -o nbody nbody.cpp
    ```
    
## Running the Simulation

### Input Format

The program requires 4 input values:
1. **Number of particles**: The total number of particles to simulate.
2. **Time step (`dt`)**: The time step size for each iteration.
3. **Number of steps**: The total number of iterations to run the simulation.
4. **Dump frequency**: How often the data is saved to the output file.

### Example Commands

- **Solar System Simulation** (12 particles):

    ```bash
    ./nbody <<EOF
    12
    200
    5000000
    1000
    EOF
    ```

- **100 Particles, `dt=1`, 10,000 Steps**:

    ```bash
    ./nbody <<EOF
    100
    1
    10000
    100
    EOF
    ```

- **1000 Particles, `dt=1`, 10,000 Steps**:

    ```bash
    ./nbody <<EOF
    1000
    1
    10000
    100
    EOF
    ```
