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

//void hist_com() {
//  int f, i, j, d;
//
//  /********************************************************/
//  // Allocate memory and initialize t, com
//  com = (double***)calloc(frs, sizeof(double**));
//  for (f=0; f<frs; f++) {
//    com[f] = (double**)calloc(nch, sizeof(double*));
//    for (i=0; i<nch; i++)
//      com[f][i] = (double*)calloc(3, sizeof(double));
//  }
//
//  int res = 10;
//  double *z = (double*)calloc(res, sizeof(double));
//  for (i=0; i<res; i++) {
//    z[i] = i*length+minimum;
//  }
//  hist = (double**)calloc(frs, sizeof(double*));
//  for (f=0; f<frs; f++)
//    hist[f] = (double*)calloc(res, sizeof(double));
//
//	/********************************************************/
//  // center of mass
//  for (f=0; f<frs; f++) {
//    for (i=0; i<nch; i++) {
//      for (j=0; j<chl; j++) {
//        for (d=0; d<3; d++) {
//          com[f][i][d] += x[f][i*chl+j][d]/chl;
//        }
//      }
//    }
//  }
//}

void hist_rg() {

  int f, i, j, k, d, bin;

  // Allocate memory for RG
  rg = (double**)calloc(frs,sizeof(double*));
  for (f=0; f<frs; f++)
    rg[f] = (double*)calloc(nch,sizeof(double));

  double bounds[] = {1 , sq(10)};
  double size = (bounds[1] - bounds[0]) / res;
  double base = pow(bounds[1]/bounds[0],1.0/res);

  prg = (double**)calloc(res,sizeof(double*));
  printf("allocating memory\n");
  for (i=0; i<res; i++) {
    prg[i] = (double*)calloc(2,sizeof(double));
    //prg[i][0] = size*i + bounds[0];
    prg[i][0] = bounds[0]*pow(base,i);
  }

  // Calculate RG
  // loop over each frame
  printf("start loop\n");
  fflush(stdout);
  for (f=0; f<frs; f++) {
    // loop over number of chains
    // nch * chl = N
    // i*nch+j = atomid
    for (i=0; i<nch; i++) {
      // loop over the atoms in each chain twice
      for (j=0; j<chl-1; j++) {
        for (k=j+1; k<chl; k++) {
          // printf("%d, %d, %d, %d\n",f,i,j,k);
          rg[f][i] += (sq(x[f][i*chl+j][0] - x[f][i*chl+k][0]) \
                   +   sq(x[f][i*chl+j][1] - x[f][i*chl+k][1]) \
                   +   sq(x[f][i*chl+j][2] - x[f][i*chl+k][2])) / sq(chl);
        }
      }
      //bin = int((rg[f][i] - bounds[0]) / size);
      bin = int(log(rg[f][i]/bounds[0])/log(base));
      prg[bin][1] += 1.0; // / (nbond*frs);
    }
  }
}

void hist_re() {

  int f, i, j, k, d, bin;
  // Allocate memory for RE
  re = (double***)calloc(frs,sizeof(double**));
  for (f=0; f<frs; f++) {
    re[f] = (double**)calloc(nch,sizeof(double*));
    for (i=0; i<nch; i++)
      re[f][i] = (double*)calloc(3,sizeof(double));
  }

  double bounds[] = {1 , sq(50)};
  double size = (bounds[1] - bounds[0]) / res;
  double base = pow(bounds[1]/bounds[0],1.0/res);

  pre = (double**)calloc(res,sizeof(double*));
  printf("allocating memory\n");
  for (i=0; i<res; i++) {
    pre[i] = (double*)calloc(2,sizeof(double));
    //pre[i][0] = size*i + bounds[0];
    pre[i][0] = bounds[0]*pow(base,i);
  }

  // Calculate RE
  // loop over each frame
  for (f=0; f<frs; f++) {
    // loop over number of chains
    // nch * chl = N
    // i*nch+j = atomid
    for (i=0; i<nch; i++) {
      // loop over the atoms in each chain twice
      for (j=0; j<chl-1; j++) {
        re[f][i][0] += bonds[f][i*(chl-1)+j][0];
        re[f][i][1] += bonds[f][i*(chl-1)+j][1];
        re[f][i][2] += bonds[f][i*(chl-1)+j][2];
      }
      re[f][i][0] = sq(re[f][i][0]) + sq(re[f][i][1]) + sq(re[f][i][2]);
      //bin = int(re[f][i][0] / size);
      bin = int(log(re[f][i][0]/bounds[0])/log(base));
      pre[bin][1] += 1.0; // / (nbond*frs);
    }
  }
}
