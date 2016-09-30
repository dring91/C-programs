/*
 * Author: David Ring
 */
#include <cstdlib>
#include <cstdio>

#include "globals.h"
#include "functions.h"

// declare globals:
//  boxh, x, N, frs, real_x
int frs, N, nch, chl, *t;
double ***x;

int main(int argc, char *argv[]) {
  // array sizes:
  // sizeof(double) = 8
  // sizeof(boxh) = 6*5*8 = 240 b
  // sizeof(x) = 3*20,000*5*8 = 2,400,000 b = 2.3 mb
  // sizeof(real_x) = 3*20,000*5*8 = 2,400,000 b = 2.3 mb

  // setup the input file
  const char *filename = argv[1];
  const char *filename_out = argv[2];
  float frac = atof(argv[3]);
  frs = atoi(argv[4]);
  N = atoi(argv[5]);
  chl = atoi(argv[6]);
  nch = N/chl;

  t = (int*)calloc(frs,sizeof(int));

  int f,n;
  x = (double***)calloc(frs,sizeof(double**));
  for (f=0; f<frs; f++) {
    x[f] = (double**)calloc(N,sizeof(double*));
    for (n=0; n<N; n++)
      x[f][n] = (double*)calloc(3,sizeof(double));
  }

  // read in the data
  read_dump(filename);

  // unwrap coordinates
  // unwrap();

  // calculate the com
  com(filename_out);

  //free(boxh);
  free(x);
  free(t);

  return 0;

}
