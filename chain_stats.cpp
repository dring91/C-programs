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
double ***x, ***com, **rg, **re;

int main(int argc, char *argv[]) {
  // array sizes:
  // sizeof(double) = 8
  // sizeof(boxh) = 6*5*8 = 240 b
  // sizeof(x) = 3*20,000*5*8 = 2,400,000 b = 2.3 mb
  // sizeof(real_x) = 3*20,000*5*8 = 2,400,000 b = 2.3 mb

  // setup the input file
  FILE *COM_RG_RE;
  const char *filename = argv[1];
  const char *filename_out = argv[2];
  frs = atoi(argv[3]);
  N = atoi(argv[4]);
  chl = atoi(argv[5]);
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
  calc_com();
  calc_rg();
  calc_re();

	/********************************************************/
	COM_RG_RE = fopen(filename_out, "w");
	if (COM_RG_RE == NULL) {
		fprintf(stderr, "Failed to open data.out\n");
		exit(1);
	}

  int i;
	for (f=0; f<frs; f++) {
    fprintf(COM_RG_RE, "#   time     com_x      com_y        com_z      rg       re\n");
    for (i=0; i<nch; i++) {
		  fprintf(COM_RG_RE, "%10d  %20.10f  %20.10f  %20.10f  %20.10f  %20.10f\n", \
                    t[f], com[f][i][0], com[f][i][1], com[f][i][2], rg[f][i], re[f][i]);
    }
    fprintf(COM_RG_RE, "\n\n");
	}

	fclose(COM_RG_RE);
  /********************************************************/

  free(x);
  free(t);

  return 0;

}
