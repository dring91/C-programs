/*
 * Author: David Ring
 */
#include <cstdlib>
#include <cstdio>

#include "globals.h"
#include "functions.h"

// declare globals:
//  boxh, x, N, frs, real_x
int frs;
int N;
double ***x;
int *t;

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

  int i,j;
  x = (double***)calloc(frs,sizeof(double**));
  for (i=0; i<frs; i++) {
    x[i] = (double**)calloc(N,sizeof(double*));
    for (j=0; j<N; j++)
      x[i][j] = (double*)calloc(3,sizeof(double));
  }

  // read in the data
  read_dump(filename);
  printf("File read\n");
  fflush(stdout);

  // unwrap the trajectory
  //unwrap_trajectory();
  
  // calculate the msd
  msd_time(filename_out,frac);
  printf("msd calculated\n");
  fflush(stdout);

  //free(boxh);
  free(x);
  //free(real_x);

  return 0;

}
