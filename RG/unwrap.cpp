/*
 * author: David Ring
 */

#include <cstdlib>
#include <cstdio>

#include "globals.h"
#include "functions.h"

void unwrap() {

  // loop through polymer molecules, calculate bond lengths, and apply periodic conditions
    
  int f, i, j, d;
  for (f=0; f<frs; f++) {
    for (i=0; i<nch; i++) {
      // skip the first atom since it acts as the anchor
      for (j=0; j<chl-1; j++) {
        for (d=0; d<3; d++) {
          x[f][i*chl+j+1][d] = periodic(x[f][i*chl+j+1][d]-x[f][i*chl+j][d], \
                                        x[f][i*chl+j+1][d], \
                                        box[f][d][1]-box[f][d][0]);
        }
      }
    }
  }

}

double periodic(double dist, double coord, double L) {

  int i;
  if (dist >= 0.5*L)
    coord -= L;
  else if (dist < -0.5*L)
    coord += L;

  return coord;

}
