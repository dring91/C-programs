/*        rg_re_com.cpp
 *        
 *        START: 09/30/16         LAST UPDATE:
 *        PROJECT: MD simulation of LJ polymers
 *        SCOPE: Program calculates: 
 *            1. Radius of gyration (distribution and its statistics)
 *            2. End-to-end distance (same)
 *            3. Center of mass
 *        AUTHOR: David Ring
 *        DEVELOPMENT:
 *
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "globals.h"
#include "functions.h"

void com(const char *filename) {
    int f, i, j, d;
    double ***com;
    FILE *COM;

    /********************************************************/
    // Allocate memory and initialize t, com
    com = (double***)calloc(frs, sizeof(double**));
    for (f=0; f<frs; f++) {
      com[f] = (double**)calloc(nch, sizeof(double*));
      for (i=0; i<nch; i++)
        com[f][i] = (double*)calloc(3, sizeof(double));
    }

	/********************************************************/
  // center of mass
  for (f=0; f<frs; f++) {
    for (i=0; i<nch; i++) {
      for (j=0; j<chl; j++) {
        for (d=0; d<3; d++) {
          com[f][i][d] += x[f][i*chl+j][d]/chl;
        }
      }
    }
  }

	/********************************************************/
	COM = fopen(filename, "w");
	if (COM == NULL) {
		fprintf(stderr, "Failed to open com.out\n");
		exit(1);
	}

	for (f=0; f<frs; f++) {
    for (i=0; i<nch; i++) {
		  fprintf(COM, "%10d  %20.10f  %20.10f  %20.10f\n", t[f], com[f][i][0], com[f][i][1], com[f][i][2]);
    }
	}

	fclose(COM);

    /********************************************************/
    free(com);
}
