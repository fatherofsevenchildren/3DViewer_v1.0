#ifndef VIEWER_H
#define VIEWER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double* vertexes;
  int* vectors;
  double* vecs;
  int draw_vectors_count;
  int vertexes_count;
  int vectors_count;  // number of vertexes in all poligon;
} arr;

typedef struct {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
} minmax_t;

void getMinMax(arr progect, minmax_t* frame);
void centralization(minmax_t frame, arr* progect);
void normalization(arr* progect, minmax_t* frame);
void verts4vecs(arr* progect);
void scal(const minmax_t* frame, arr* progect, double value);
void free_arr(arr* project);
// ---------affine ------
void Moving(arr* progect, double value, char c);
void RotateX(arr* progect, double value);
void RotateY(arr* progect, double value);
void RotateZ(arr* progect, double value);

/// @brief
/// @param str name if file
/// @param progect final struct
/// @return 0 if all right, 2 if file not found
int parser(char* str, arr* progect, minmax_t* frame);

#endif  // VIEWER_H
