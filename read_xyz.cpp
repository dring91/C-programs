/*        read_xyz.cpp
 *        
 *        START: 09/22/16         LAST UPDATE:
 *        AUTHOR: David Ring (based on read_dump by Emily Lin)
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
	int f, i;
	int dummy;
	char dummyline[200];

	// Open the file dump.traj
	FILE *input;
	input = fopen(filename,"r");
	if (input == NULL) {
		fprintf(stderr, "Failed to open dump.xyz\n");
		exit(1);
	}
	
	for (f=0; f<frs; f++) {
		// ignore the first two lines of dump.xyz
    fgets(dummyline, 200, input);
    fscanf(input, "%s %s %d\n", dummyline, dummyline, &t[f]);
		// Read and store the x y z positions of each particle 
		// rearrange them so the position matrix start with 
		// particle 1, 2, ... N
		for (i=0; i<N; i++) {
			fscanf(input, "%d %lf %lf %lf\n", \
             &dummy, \
					   &x[f][i][0], \
             &x[f][i][1], \
					   &x[f][i][2]); 
		}
	}

	fclose(input);
}

