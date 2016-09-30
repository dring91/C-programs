/*        msd_time.cpp
 *        
 *        START: 03/22/16         LAST UPDATE:
 *        PROJECT: MD simulation of LJ and LJ_expand polymer system
 *        SCOPE: Program calculates: 
 *            1. g(r) calculations
 *            2. MSD
 *        AUTHOR: Emily Lin
 *        DEVELOPMENT:
 *
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "globals.h"
#include "functions.h"

void msd_time(const char *filename, float frac) {
    int i, j, f;
    double *t, *msd, r2_sum, dr[3];
    FILE *MSD;

    // Define time origin shift related parameters
    // to = frame number that corresponds to time origin 
    // ff = number of frames in each set of data = 45
    int to, ff, n_data; 

    n_data = int(frac*double(frs));
    ff = frs - n_data;
    /********************************************************/
    // Allocate memory and initialize r2, t, and D
    msd = (double*)calloc((ff), sizeof(double));
    t = (double*)calloc((ff), sizeof(double));
    for (f=0; f<(ff); f++) {
        t[f] = 0.0;
        msd[f] = 0.0;
    }

	/********************************************************/
    // Outer most loops over different time origins
    for (to=0; to<n_data; to++) {
        // Loop over all the time frames within each time origin set
        for (f=to; f<(ff+to); f++) {
            r2_sum = 0.0;
            for (i=0; i<N; i++) {
                for (j=0; j<3; j++) {
                    dr[j] = x[f][i][j] - x[to][i][j];
                    r2_sum += dr[j]*dr[j];
                }
            }
            // Update msd with new data in the new time origin
            msd[f-to] += r2_sum/N;
        }
    }
    // Correct msd with number of data sets
    for (i=0; i<ff; i++) {
        msd[i] /= n_data;
    }

	/********************************************************/
	MSD = fopen(filename, "w");
	if (MSD == NULL) {
		fprintf(stderr, "Failed to open msd.out\n");
		exit(1);
	}
	// calculate t //FIXME input correct time step here!!!
	for (f=0; f<(ff); f++) {
		t[f] = f*10000; //Each frame represents 200,000 time steps
	}
	// Write t and r2 in file, skip t = 0, msd = 0 point
	for (f=1; f<(ff); f++) {
		fprintf(MSD, "%20.10f  %20.10f\n", t[f], msd[f]);
	}
	fclose(MSD);

    /********************************************************/
    free(t);
    free(msd);
}
