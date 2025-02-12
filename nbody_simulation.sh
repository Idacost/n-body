#!/bin/bash
#SBATCH --job-name=nbody_simulation
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32GB
#SBATCH --output=simulation_output.txt

echo "Running simulation..."

(time ./nbody <<EOF
12
200
5000000
1000
EOF
) 2>&1 | tee solar_simulation_time.txt

(time ./nbody <<EOF
100
1
10000
100
EOF
) 2>&1 | tee sim_100_particles_time.txt

(time ./nbody <<EOF
1000
1
10000
100
EOF
) 2>&1 | tee sim_1000_particles_time.txt

