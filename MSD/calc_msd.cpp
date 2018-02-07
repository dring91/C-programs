/*
 * Author: David Ring
 */
#include <cstdlib>
#include <cstdio>

void write_data
  (const char *filename, int frames, int *t, double *msd)
{
  FILE *MSD;
	MSD = fopen(filename, "w");
	if (MSD == NULL) {
		fprintf(stderr, "Failed to open msd.out\n");
		exit(1);
	}
	// Write t and r2 in file, skip t = 0, msd = 0 point
  int f;
	for (f=1; f<frames; f++) {
    t[f] -= t[0];
		fprintf(MSD, "%d  %20.10f\n", t[f], msd[f]);
	}
	fclose(MSD);
}

void read_dump
  (const char *filename, int frames, int N, int *t, int **types, double ***box, double ***x) 
{
  int d = 3;
	int f, i, id;
	char dummyline[200];
  double dummy;

	// Open the file dump.traj
	FILE *input;
	input = fopen(filename,"r");
	if (input == NULL) {
		fprintf(stderr, "Failed to open dump.traj\n");
		exit(1);
	}

	for (f=0; f<frames; f++) {
		// Start reading dump.traj and ignore the first line
    fgets(dummyline, 200, input);
    // read the timestep
    fscanf(input, "%d\n", &t[f]);
    //printf("%d\n", t[f]);
		// ignore the next 3 lines
    fgets(dummyline, 200, input);
    // read the number of atoms
    fscanf(input, "%d\n", &N);
    //printf("%d\n", N);
		// Read and store the box size at each time frame
    fgets(dummyline, 200, input);
		for (i=0; i<d; i++) {
			fscanf(input, "%lf %lf\n", &box[f][i][0], &box[f][i][1]);
		}
		// Read another line and ignore
		fgets(dummyline, 200, input);
    //printf("%s\n", dummyline);
		// Read and store the x y z positions of each particle 
		// rearrange them so the position matrix start with 
		// particle 1, 2, ... N
		for (i=0; i<N; i++) {
      fscanf(input, "%d ", &id);
			fscanf(input, "%d ", &types[f][id-1]);
			fscanf(input, "%lf %lf %lf %lf\n", \
					&x[f][id-1][0], \
          &x[f][id-1][1], \
					&x[f][id-1][2], \
          &dummy); 
		}
	}

	fclose(input);
}

int add(int N, int *arr, int num)
{
  int total = 0;
  for(int i=0; i<N; i++) {
    if (arr[i] == num)
      total += 1;
  }
  return total;
}

void select(int frames, int N, int ptype, int **types, double ***X, double ***x) 
{
  int f,i,d;
  for(f=0; f<frames; f++) {
    int j=0;
    for(i=0; i<N; i++){
      if(types[f][i] == ptype) {
        for(d=0; d<3; d++) {
          x[f][j][d] = X[f][i][d];
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {

  if(argc < 6)
    printf("not enough commandline arguments");
  // read in the command line arguments:
  // input file name
  const char *filename_in = argv[1];
  // output file name
  const char *filename_out = argv[2];
  // how many time origins to use
  int origins = atof(argv[3]);
  // number of frames to run the calculation with (<= the number of frames in trajectory)
  int frames = atoi(argv[4]);
  // the number of atoms in each frame
  int N = atoi(argv[5]);

  const int d = 3;
  int f,n;
  double ***x;
  x=(double***)calloc(frames,sizeof(double**));
  for (f=0; f<frames; f++) {
    x[f] = (double**)calloc(N,sizeof(double*));
    for (n=0; n<N; n++)
      x[f][n] = (double*)calloc(d,sizeof(double));
  }

  double ***box;
  box=(double***)calloc(frames,sizeof(double**));
  for (f=0; f<frames; f++) {
    box[f]=(double**)calloc(d,sizeof(double*));
    for (n=0; n<d; n++)
      box[f][n]=(double*)calloc(2,sizeof(double));
  }

  int *t;
  t=(int*)calloc(frames,sizeof(int));

  int **types;
  types=(int**)calloc(frames,sizeof(int*));
  for (f=0; f<frames; f++)
    types[f]=(int*)calloc(N,sizeof(int));
	
  // read in the data
  read_dump(filename_in, frames, N, t, types, box, x);
  printf("dump file read\n");
  // compute how many atoms in a frame belong in a polymer
  int n_poly = add(N,types[0],2);
  // allocate array for only polymers
  double ***poly;
  poly=(double***)calloc(frames,sizeof(double**));
  for(f=0; f<frames; f++) {
    poly[f]=(double**)calloc(n_poly,sizeof(double*));
    for(n=0; n<n_poly; n++)
      poly[f][n]=(double*)calloc(3,sizeof(double));
  }
  // select only the polymer atoms to calculate on
  select(frames, N, 2, types, x, poly);

  // calculate the msd
  int to, ff, i, j;
  double *msd;
  double r2_sum, dr[3];

  // Define time origin shift related parameters
  // to = frame number that corresponds to time origin 
  // ff = number of frames in each set of data = 45

  ff = frames - origins;
  /********************************************************/
  // Allocate memory and initialize r2, t, and D
  msd = (double*)calloc((ff), sizeof(double));
  for (f=0; f<(ff); f++) {
      msd[f] = 0.0;
  }

	/********************************************************/
  // Outer most loops over different time origins
  for (to=0; to<origins; to++) {
      // Loop over all the time frames within each time origin set
      for (f=to; f<(ff+to); f++) {
          r2_sum = 0.0;
          for (i=0; i<N; i++) {
              for (j=0; j<3; j++) {
                  dr[j] = x[f][i][j] - x[to][i][j];
                  r2_sum += dr[j]*dr[j];
              }
          }
          // Update msd with new data in the new time origin
          msd[f-to] += r2_sum/N;
      }
  }
  // Correct msd with number of data sets
  for (i=0; i<ff; i++) {
      msd[i] /= origins;
  }

  // write out the data
  write_data(filename_out, ff, t, msd);

  // free multi-dimensional arrays
  for (f=0; f<frames; f++) {
    for (n=0; n<N; n++)
      free(x[f][n]);
    for (n=0; n<n_poly; n++)
      free(poly[f][n]);
    for (j=0; j<3; j++)
      free(box[f][j]);
    free(x[f]);
    free(types[f]);
  }
  free(x);
  free(types);

  // free single arrays
  free(t);
  free(msd);

  return 0;

}
