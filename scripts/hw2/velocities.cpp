/*----------------------------------------------------------------------------
This script randomly assigns velocities to atoms.
It is assumed that all atoms have the same velocity magnitude.
----------------------------------------------------------------------------*/

#include <cstdlib>                            // Random number generator

void velocities(
                long double vx[],
                long double vy[],
                long double vz[],
                int atoms,
                long double temperature
                )
{
    long double tempper = temperature*(3.0);  // The temperature for each atom

    // Random number on unit sphere
    long double s;
    long double zeta0;
    long double zeta1;
    long double xi0[atoms];
    long double xi1[atoms];
    long double xi2[atoms];

    int i = 0;
    while(i < atoms)
    {
        zeta0 = (long double) 2.0*rand()/RAND_MAX-1.0;
        zeta1 = (long double) 2.0*rand()/RAND_MAX-1.0;
        s = pow(zeta0, 2.0);
        s += pow(zeta1, 2.0);
        if(s < 1)
        {
            xi0[i] = 2*pow(1-pow(s, 2.0), 0.5)*zeta0;
            xi1[i] = 2*pow(1-pow(s, 2.0), 0.5)*zeta1;
            xi2[i] = 1-2*pow(s, 2);

            i++;  // Increment the while loop
        }
    }

    // The maginitude for calulating a unit vector
    long double mag;

    // Assign random vector directions to each atom
    for(int i = 0; i < atoms; i++)
    {
        vx[i] = xi0[i];
        vy[i] = xi1[i];
        vz[i] = xi2[i];

        mag = pow(pow(vx[i], 2.0)+pow(vy[i], 2.0)+pow(vz[i], 2.0), 0.5);

        vx[i] *= tempper/mag;
        vy[i] *= tempper/mag;
        vz[i] *= tempper/mag;
    }
}
