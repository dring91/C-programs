/*
 * Author: David
 *
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "globals.h"
#include "functions.h"

void write_traj(const char *filename) {
 
  FILE *FOUT;

  FOUT = fopen(filename, "w");
  if (FOUT == NULL) {
    fprintf(stderr, "Failed to open output file\n");
    exit(1);
  }

  int f,n;
  for (f=0; f<frs; f++) {
    fprintf(FOUT, "ITEM: TIMESTEP\n");
    fprintf(FOUT, "%d\n", t[f]);
    fprintf(FOUT, "ITEM: NUMBER OF ATOMS\n");
    fprintf(FOUT, "%d\n", N);
    fprintf(FOUT, "ITEM: BOX BOUNDS pp pp pp\n");
    fprintf(FOUT, "%f %f\n", box[f][0][0], box[f][0][1]);
    fprintf(FOUT, "%f %f\n", box[f][1][0], box[f][1][1]);
    fprintf(FOUT, "%f %f\n", box[f][2][0], box[f][2][1]);
    fprintf(FOUT, "ITEM: ATOMS id type x y z\n");
    for (n=0; n<N; n++) {
      fprintf(FOUT, "%d %d %f %f %f\n", n, 1, x[f][n][0], x[f][n][1], x[f][n][2]);
    }
  }

  fclose(FOUT);

}

void write_data(const char *filename) {

  FILE *FOUT = fopen(filename, "w");
  if (FOUT == NULL) {
    fprintf(stderr, "Failed to open output file\n");
    exit(1);
  }

  int f,n;
  fprintf(FOUT, "#   time    com_x    com_y     com_z      rg      re\n");
  for (f=0; f<frs; f++) {
    fprintf(FOUT, "%8d ", t[f]);
    // fprintf(FOUT, "%20.10f  %20.10f  %20.10f  ", com[f][n][0], com[f][n][1], com[f][n][2]);
    fprintf(FOUT, "%20.10f  ", sqrt(rg[f]));
    fprintf(FOUT, "%20.10f\n", sqrt(re[f][0]));
  }
  fprintf(FOUT, "\n\n");

  fclose(FOUT);

}
