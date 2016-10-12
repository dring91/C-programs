/*
 * Author: David Ring
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "globals.h"
#include "functions.h"

// declare globals:
int frs, N, nch, chl, nbond, *t;
double ***x, ***com, ***bonds; 
double *rg, **re, ***box;

int main(int argc, char *argv[]) {

  // setup the input file
  const char *filename = argv[1];
  const char *filename_out = argv[2];
  frs = atoi(argv[3]);
  N = atoi(argv[4]);
  chl = atoi(argv[5]);
  nch = N/chl;
  nbond = nch*(chl-1);

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
  printf("input file read\n");
  fflush(stdout);

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
  printf("bond vectors calculated\n");
  fflush(stdout);

  // unwrap the polymers
  // unwrap();
  // printf("trajectory molecules unwrapped\n");
  // fflush(stdout);

  // calculate the com
  //calc_com();
  //calc_rg();
  //calc_re();
  ave_rg();
  ave_re();

  // write_traj("unwrapped_traj.lammpstrj");
  write_data(filename_out);

  free(x);
  free(t);
  free(com);
  free(rg);
  free(re);
  free(bonds);

  return 0;

}
