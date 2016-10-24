/*        read_dump.cpp
 *        
 *        START: 03/22/16         LAST UPDATE:
 *        PROJECT: MD simulation of LJ and LJ_expand polymer system
 *        SCOPE: Program calculates: 
 *            1. g(r) calculations
 *            2. MSD
 *        AUTHOR: Emily Lin
 *        DEVELOPMENT:
 *
 */
#include <cstdlib>
#include <cstdio>
#include <cmath> 

#include "globals.h"
#include "functions.h"

//Read input dump.traj type file
void read_dump(const char *filename) {
	int f, i, id;
	double dummy;
	char dummyline[200];

	// Open the file dump.traj
	FILE *input;
	input = fopen(filename,"r");
	if (input == NULL) {
		fprintf(stderr, "Failed to open dump.traj\n");
		exit(1);
	}

  box=(double***)calloc(frs,sizeof(double**));
  for (f=0; f<frs; f++) {
    box[f]=(double**)calloc(3,sizeof(double*));
    for (i=0; i<3; i++)
      box[f][i]=(double*)calloc(2,sizeof(double));
  }

  t=(int*)calloc(frs,sizeof(int));
	
	for (f=0; f<frs; f++) {
		// Start reading dump.traj and ignore the first line
    fgets(dummyline, 200, input);
    // read the timestep
    fscanf(input, "%d\n", &t[f]);
    printf("%d\n", t[f]);
		// ignore the next 3 lines
    fgets(dummyline, 200, input);
    // read the number of atoms
    fscanf(input, "%d\n", &N);
    printf("%d\n", N);
		// Read and store the box size at each time frame
    fgets(dummyline, 200, input);
		for (i=0; i<3; i++) {
			fscanf(input, "%lf %lf\n", &box[f][i][0], &box[f][i][1]);
		}
		// Read another line and ignore
		fgets(dummyline, 200, input);
    printf("%s\n", dummyline);
		// Read and store the x y z positions of each particle 
		// rearrange them so the position matrix start with 
		// particle 1, 2, ... N
		for (i=0; i<N; i++) {
      fscanf(input, "%d ", &id);
			fscanf(input, "%lf %lf %lf %lf\n", &dummy, \
					&x[f][id-1][0], \
          &x[f][id-1][1], \
					&x[f][id-1][2]); 
		}
	}

	fclose(input);
}

