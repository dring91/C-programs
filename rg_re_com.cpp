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

double sq(double x) {
  return x*x;
}

void calc_com() {
  int f, i, j, d;

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

  free(com);
}

void calc_rg() {

  int f, i, j, k, d;

  // Allocate memory for RG
  double **rg;
  rg = (double**)calloc(frs,sizeof(double*));
  for (f=0; f<frs; f++)
    rg[f] = (double*)calloc(nch,sizeof(double));

  // Calculate RG
  // loop over each frame
  for (f=0; f<frs; f++) {
    // loop over number of chains
    // nch * chl = N
    // i*nch+j = atomid
    for (i=0; i<nch; i++) {
      // loop over the atoms in each chain twice
      for (j=0; j<chl; j++) {
        for (k=j; k<chl+1; k++) {
          rg[f][i] += (sq(x[f][i*nch+j][0] - x[f][i*nch+k][0]) \
                   +   sq(x[f][i*nch+j][1] - x[f][i*nch+k][2]) \
                   +   sq(x[f][i*nch+j][2] - x[f][i*nch+k][1])) / sq(chl);
        }
      }
    }
  }

}

void calc_re() {

  int f, i, j, k, d;
  // Allocate memory for RE
  double **re;
  re = (double**)calloc(frs,sizeof(double*));
  for (f=0; f<frs; f++)
    re[f] = (double*)calloc(nch,sizeof(double));

  // Calculate RG
  // loop over each frame
  for (f=0; f<frs; f++) {
    // loop over number of chains
    // nch * chl = N
    // i*nch+j = atomid
    for (i=0; i<nch; i++) {
      // loop over the atoms in each chain twice
      for (j=0; j<chl; j++) {
        for (k=0; k<chl; k++) {
          re[f][i] += (x[f][i*chl+j][0]*x[f][i*chl+k][0] \
                   +   x[f][i*chl+j][1]*x[f][i*chl+k][1] \
                   +   x[f][i*chl+j][2]*x[f][i*chl+k][2])  / sq(chl);
        }
      }
      re[f][i] = sqrt(re[f][i]);
    }
  }

}
