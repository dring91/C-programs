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
double ***x, ***com, ***bonds; 
double **rg, **re;

int main(int argc, char *argv[]) {

  // setup the input file
  FILE *FOUT;
  const char *filename = argv[1];
  const char *filename_out = argv[2];
  frs = atoi(argv[3]);
  N = atoi(argv[4]);
  chl = atoi(argv[5]);
  nch = N/chl;
  int nbond = nch*(chl-1);
  printf("%d, %d\n",nch,nbond);

  t = (int*)calloc(frs,sizeof(int));

  int f,n;
  x = (double***)calloc(frs,sizeof(double**));
  for (f=0; f<frs; f++) {
    x[f] = (double**)calloc(N,sizeof(double*));
    for (n=0; n<N; n++)
      x[f][n] = (double*)calloc(3,sizeof(double));
  }

  bonds = (double***)calloc(frs,sizeof(double**));
  for (f=0; f<frs; f++) {
    bonds[f] = (double**)calloc(nbond,sizeof(double*));
    for (n=0; n<nbond; n++)
      bonds[f][n] = (double*)calloc(3,sizeof(double));
  }

  // read in the data
  read_dump(filename);
  printf("File read\n");

  // unwrap coordinates
  // unwrap();
  
  // Generate bond vectors for each polymer
  int i,j;
  for (f=0; f<frs; f++) {
    for (i=0; i<nch; i++) {
      for (j=0; j<chl-1; j++) {
        bonds[f][i*(chl-1)+j][0] = x[f][i*chl+j+1][0]-x[f][i*chl+j][0];
        bonds[f][i*(chl-1)+j][1] = x[f][i*chl+j+1][1]-x[f][i*chl+j][1];
        bonds[f][i*(chl-1)+j][2] = x[f][i*chl+j+1][2]-x[f][i*chl+j][2];
      }
    }
  }

  // calculate the com
  calc_com();
  printf("calculated COM\n");
  fflush(stdout);
  calc_rg();
  printf("calculated RG\n");
  fflush(stdout);
  calc_re();
  printf("calculated RE\n");
  fflush(stdout);

	/********************************************************/
	FOUT = fopen(filename_out, "w");
	if (FOUT == NULL) {
		fprintf(stderr, "Failed to open data.out\n");
		exit(1);
	}

	for (f=0; f<frs; f++) {
    fprintf(FOUT, "#   time     com_x      com_y        com_z      rg       re\n");
    fflush(FOUT);
    for (i=0; i<nch; i++) {
		  fprintf(FOUT, "%8d  ", t[f]);
		  fprintf(FOUT, "%20.10f  %20.10f  %20.10f  ", com[f][i][0], com[f][i][1], com[f][i][2]);
		  fprintf(FOUT, "%20.10f  ", rg[f][i]);
		  fprintf(FOUT, "%20.10f\n", re[f][i]);
    }
    fprintf(FOUT, "\n\n");
    fflush(FOUT);
	}

	fclose(FOUT);
  /********************************************************/

  free(x);
  free(t);
  free(com);
  free(rg);
  free(re);
  free(bonds);

  return 0;

}
