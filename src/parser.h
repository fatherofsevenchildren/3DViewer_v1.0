#ifndef VIEWER_H
#define VIEWER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  double* vertexes;
  int* vectors;

  int vertexes_count; 
  int vecotrs_count; // number of vertexes in all poligon;
  

  int x_min;
  int x_max;
  int y_min;
  int y_max;
  int z_min;
  int z_max;
} data;

/// @brief
/// @param str name if file
/// @param progect final struct
/// @return 0 if all right, 2 if file not found

int parser(char* str, data* progect);

#endif  // VIEWER_H