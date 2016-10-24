/*
 * Author: David Ring
 */
#include <cstdlib>
#include <cstdio>

#include "globals.h"
#include "functions.h"

// declare globals:
int frs;
int N;
double ***x;
int *t;

int main(int argc, char *argv[]) {

  // read in the command line arguments:
  // input file name
  const char *filename = argv[1];
  // output file name
  const char *filename_out = argv[2];
  // determines how many time origins to use. stick to 0.1
  float frac = atof(argv[3]);
  // number of frames to run the calculation with (<= the number of frames in trajectory)
  frs = atoi(argv[4]);
  // the number of atoms in each frame
  N = atoi(argv[5]);

  int f,n;
  x = (double***)calloc(frs,sizeof(double**));
  for (f=0; f<frs; f++) {
    x[f] = (double**)calloc(N,sizeof(double*));
    for (n=0; n<N; n++)
      x[f][n] = (double*)calloc(3,sizeof(double));
  }

  // read in the data
  read_dump(filename);

  // calculate the msd
  msd_time(filename_out,frac);

  for (f=0; f<frs; f++) {
    for (n=0; n<N; n++)
      free(x[f][n]);
    free(x[f]);
  }
  free(x);

  return 0;

}
