/*        globals.h
 *        
 *        AUTHOR: Emily Lin
 *        MODIFIED BY: David Ring
 */

// Number of frames and number of time steps per frame
#ifndef MAIN
extern
#endif
	int frs, timestep, *t; 

// Number of particles, number of polymer chains, length of polymer chain
#ifndef MAIN
extern 
#endif
	int res, N, nch, chl, nbond;

// Frame number and position stored in one 3D array
#ifndef MAIN
extern
#endif
	double ***x, ***real_x, ***com, ***bonds; 

#ifndef MAIN
extern
#endif
  double **prg, **pre, **rg, ***re, ***box;

// Time step size
#ifndef MAIN
extern
#endif
	double stepsize;
