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
double ***x, ***positions, **bonds; 
double ***box;

double sq(double x) {return x*x;}

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
  positions = (double***)calloc(frs,sizeof(double**));
  bonds = (double**)calloc(frs,sizeof(double*));
  for (f=0; f<frs; f++) {
    x[f] = (double**)calloc(N,sizeof(double*));
    positions[f] = (double**)calloc(nbond,sizeof(double*));
    bonds[f] = (double*)calloc(nbond,sizeof(double));
    for (n=0; n<N; n++)
      x[f][n] = (double*)calloc(3,sizeof(double));
    for (n=0; n<nbond; n++)
      positions[f][n] = (double*)calloc(3,sizeof(double));
  }

  // read in the data
  read_dump(filename);

  // unwrap the polymers
  unwrap();

  int i,j;
  printf("calculating bond lengths\n");
  for (f=0; f<frs; f++) {
    for (i=0; i<nch; i++) {
      for (j=0; j<chl-1; j++) {
        bonds[f][i*(chl-1)+j] = sqrt(sq(x[f][i*chl+j+1][0]-x[f][i*chl+j][0]) \
                                   + sq(x[f][i*chl+j+1][1]-x[f][i*chl+j][1]) \
                                   + sq(x[f][i*chl+j+1][2]-x[f][i*chl+j][2]));
        positions[f][i*(chl-1)+j][0] = x[f][i*chl+j][0];
        positions[f][i*(chl-1)+j][1] = x[f][i*chl+j][1];
        positions[f][i*(chl-1)+j][2] = x[f][i*chl+j][2];
      }
    }
  }

  // write out the bond lengths
  write_data(filename_out);

  free(t);
  free(x);
  free(bonds);
  free(positions);

  return 0;

}
