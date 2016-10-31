/*
 * Author: David Ring
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "globals.h"
#include "functions.h"

// declare globals:
int res, frs, N, nch, chl, nbond, *t;
double ***x, **prg, **pre, ***bonds; 
double **rg, ***re, ***box;

int main(int argc, char *argv[]) {

  // setup the input file
  const char *filename = argv[1];
  const char *filename_out = argv[2];
  // number of frames in trajectory to analyze
  frs = atoi(argv[3]);
  // total number of polymer atoms
  N = atoi(argv[4]);
  // number of units to a chain
  chl = atoi(argv[5]);
  // number of chains in the trajectory
  nch = N/chl;
  nbond = nch*(chl-1);
  // number of bins in the probability distributions
  res = atoi(argv[6]);

  int f,n;
  x = (double***)calloc(frs,sizeof(double**));
  bonds = (double***)calloc(frs,sizeof(double**));
  for (f=0; f<frs; f++) {
    x[f] = (double**)calloc(N,sizeof(double*));
    bonds[f] = (double**)calloc(nbond,sizeof(double*));
    for (n=0; n<N; n++)
      x[f][n] = (double*)calloc(3,sizeof(double));
    for (n=0; n<nbond; n++)
      bonds[f][n] = (double*)calloc(3,sizeof(double));
  }

  // read in the data
  read_dump(filename);

  int i,j;
  for (f=0; f<frs; f++) {
    // calculate bond vectors
    for (i=0; i<nch; i++) {
      for (j=0; j<chl-1; j++) {
        bonds[f][i*(chl-1)+j][0] = x[f][i*chl+j+1][0]-x[f][i*chl+j][0];
        bonds[f][i*(chl-1)+j][1] = x[f][i*chl+j+1][1]-x[f][i*chl+j][1];
        bonds[f][i*(chl-1)+j][2] = x[f][i*chl+j+1][2]-x[f][i*chl+j][2];
      }
    }
  }

  // unwrap the polymers
  printf("unwrapping coordinates\n");
  unwrap();

  // calculate RG and RE histograms
  printf("calculating rg\n");
  hist_rg();
  printf("calculating re\n");
  fflush(stdout);
  hist_re();

  // write_traj("unwrapped_traj.lammpstrj");
  write_data(filename_out);

  free(t);
  free(x);
  free(rg);
  free(re);
  free(pre);
  free(prg);
  free(bonds);

  return 0;

}
