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
}

//void calc_rg() {
//
//  int f, i, j, k, d;
//
//  // Allocate memory for RG
//  rg = (double**)calloc(frs,sizeof(double*));
//  for (f=0; f<frs; f++)
//    rg[f] = (double*)calloc(nch,sizeof(double));
//
//  // Calculate RG
//  // loop over each frame
//  for (f=0; f<frs; f++) {
//    // loop over number of chains
//    // nch * chl = N
//    // i*nch+j = atomid
//    for (i=0; i<nch; i++) {
//      // loop over the atoms in each chain twice
//      for (j=0; j<chl-1; j++) {
//        for (k=j+1; k<chl; k++) {
//          rg[f][i] += (sq(x[f][i*chl+j][0] - x[f][i*chl+k][0]) \
//                   +   sq(x[f][i*chl+j][1] - x[f][i*chl+k][1]) \
//                   +   sq(x[f][i*chl+j][2] - x[f][i*chl+k][2])) / sq(chl);
//        }
//      }
//    }
//  }
//}

void ave_rg() {

  int f, i, j, k, d;

  // Allocate memory for RG
  rg = (double*)calloc(frs,sizeof(double));

  // Calculate RG
  // loop over each frame
  for (f=0; f<frs; f++) {
    // loop over number of chains
    for (i=0; i<nch; i++) {
      // loop over the atoms in each chain twice
      for (j=0; j<chl-1; j++) {
        for (k=j+1; k<chl; k++) {
          rg[f] += (sq(x[f][i*chl+j][0] - x[f][i*chl+k][0]) \
                +   sq(x[f][i*chl+j][1] - x[f][i*chl+k][1]) \
                +   sq(x[f][i*chl+j][2] - x[f][i*chl+k][2])) / sq(chl);
        }
      }
    }
    rg[f] = rg[f] / nch;
  }
}

//void calc_re() {
//
//  int f, i, j, k, d;
//  // Allocate memory for RE
//  re = (double***)calloc(frs,sizeof(double**));
//  for (f=0; f<frs; f++) {
//    re[f] = (double**)calloc(nch,sizeof(double*));
//    for (i=0; i<nch; i++)
//      re[f][i] = (double*)calloc(3,sizeof(double));
//  }
//
//  // Calculate RG
//  // loop over each frame
//  for (f=0; f<frs; f++) {
//    // loop over number of chains
//    // nch * chl = N
//    // i*nch+j = atomid
//    for (i=0; i<nch; i++) {
//      // loop over the atoms in each chain twice
//      for (j=0; j<chl-1; j++) {
//        re[f][i][0] += bonds[f][i*(chl-1)+j][0];
//        re[f][i][1] += bonds[f][i*(chl-1)+j][1];
//        re[f][i][2] += bonds[f][i*(chl-1)+j][2];
//      }
//      re[f][i][0] = sq(re[f][i][0]) + sq(re[f][i][1]) + sq(re[f][i][2]);
//    }
//  }
//}

void ave_re() {

  int f, i;
  // Allocate memory for RE
  re = (double**)calloc(frs,sizeof(double*));
  for (f=0; f<frs; f++)
    re[f]=(double*)calloc(3,sizeof(double));

  // Calculate RG
  // loop over each frame
  for (f=0; f<frs; f++) {
    for (i=0; i<nbond; i++) {
      re[f][0] += bonds[f][i][0];
      re[f][1] += bonds[f][i][1];
      re[f][2] += bonds[f][i][2];
    }
    re[f][0] = sq(re[f][0]/nch) + sq(re[f][1]/nch) + sq(re[f][2]/nch);
  }
}
