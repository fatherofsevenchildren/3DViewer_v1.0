#define _POSIX_C_SOURCE 200809L
#include "parser.h"

/// @brief for correct allocted memory culc size of future arrays
/// @return 0 if all right, 2 if file not found

int variableCount(char* str, arr* progect) {
  FILE* fp = NULL;
  int res = 0;
  fp = fopen(str, "r");
  if (!fp) return 2;
  char* line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1 && res == 0) {
    if (line[0] == 'v' && line[1] == ' ') {
      if (strlen(line) < 7)
        res = 1;
      else
        progect->vertexes_count++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      if (strlen(line) < 5) res = 1;
      for (size_t i = 1; i < strlen(line) && res == 0; i++)
        if (line[i] == ' ' && line[i - 1] != ' ') progect->vectors_count++;
    }
  }
  free(line);
  fclose(fp);
  return res;
}

int is_num(char i) {
  int res = 1;
  if (i < '1' || i > '9') res = 0;
  return res;
}

/// @brief
/// @param str
/// @param progect
/// @return 0 - i all right, 1 - wrong poligon, 2 - can't open file
int getValue(char* str, arr* progect) {
  FILE* fp = NULL;
  fp = fopen(str, "r");
  if (!fp) return 2;
  char* line = NULL;
  size_t len = 0;
  int i = 0, j = 0, res = 0, v = 0;
  while (getline(&line, &len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ') {
      v++;
      char* cur_line = line;
      char* token = strtok(cur_line, " ");
      while (token != NULL) {
        token = strtok(NULL, " ");
        if (token) {
          progect->vertexes[i++] = atof(token);
        }
      }
    }
    if (line[0] == 'f' && line[1] == ' ') {
      char* cur_line = line;
      char* token = strtok(cur_line, " ");
      int buffer_first_vector = 0;
      int flag_first = 0;
      while (token != NULL && res == 0) {
        token = strtok(NULL, " ");
        if (token && strpbrk(token, ",.qwertyuiopasdfghjklzxcvbnm;'[=]]"))
          res = 1;  // non valid vector
        if (token && (is_num(token[0]) || token[0] == '-')) {
          if (token[0] == '-')
            progect->vectors[j++] = atoi(token) + v + 1;
          else
            progect->vectors[j++] = atoi(token);
          if (!flag_first) {
            if (token[0] == '-')
              buffer_first_vector = atoi(token) + v + 1;
            else
              buffer_first_vector = atoi(token);
            flag_first++;
          } else {
            if (token[0] == '-')
              progect->vectors[j++] = atoi(token) + v + 1;
            else
              progect->vectors[j++] = atoi(token);
          }
        } else if (token && token[0] == '0')
          res = 1;
      }
      progect->vectors[j++] = buffer_first_vector;
    }
  }
  free(line);
  fclose(fp);
  return res;
}

void getMinMax(arr progect, minmax_t* frame) {
  // minmax_t frame = {0.0,0.0,0.0,0.0,0.0,0.0};
  frame->x_max = frame->x_min = progect.vertexes[0];
  frame->y_max = frame->y_min = progect.vertexes[1];
  frame->z_max = frame->z_min = progect.vertexes[2];
  for (int i = 3; i < progect.vertexes_count * 3; i++) {
    if (!(i % 3)) {
      if (progect.vertexes[i] > frame->x_max)
        frame->x_max = progect.vertexes[i];
      if (progect.vertexes[i] < frame->x_min)
        frame->x_min = progect.vertexes[i];
    } else if (i % 3 == 1) {
      if (progect.vertexes[i] > frame->y_max)
        frame->y_max = progect.vertexes[i];
      if (progect.vertexes[i] < frame->y_min)
        frame->y_min = progect.vertexes[i];
    } else {
      if (progect.vertexes[i] > frame->z_max)
        frame->z_max = progect.vertexes[i];
      if (progect.vertexes[i] < frame->z_min)
        frame->z_min = progect.vertexes[i];
    }
  }
}

/// @brief calc maximal differences between min and max the value of the
/// coordinates
/// @param frame
/// @return res
double maxDifference(minmax_t frame) {
  double res = frame.x_max - frame.x_min;
  if ((frame.y_max - frame.y_min) > res) res = frame.y_max - frame.y_min;
  if ((frame.z_max - frame.z_min) > res) res = frame.z_max - frame.z_min;
  return res;
}

void scal(const minmax_t* frame, arr* progect, double value) {
  double max_dif = maxDifference(*frame);
  double scal = (value * 2) / max_dif;
  //  printf("\n\n%lf\n\n", scal);
  for (int i = 0; i < progect->vertexes_count * 3; i++)
    progect->vertexes[i] *= scal;
}

void centralization(minmax_t frame, arr* progect) {
  Moving(progect, 0.00 - (frame.x_min + (frame.x_max - frame.x_min) / 2), 'x');
  Moving(progect, 0.00 - (frame.y_min + (frame.y_max - frame.y_min) / 2), 'y');
  Moving(progect, 0.00 - (frame.z_min + (frame.z_max - frame.z_min) / 2), 'z');
}

/// @brief
/// @param progect
void normalization(arr* progect, minmax_t* frame) {
  getMinMax(*progect, frame);
  centralization(*frame, progect);
  //  getMinMax(*progect, frame);
  scal(frame, progect, 0.5);
  getMinMax(*progect, frame);
}

// int checkValue(arr* progect) {
//   int res = 0;
//   // for (int i = 0; i < progect->vectors_count * 2; i++) {
//     // if (progect->vectors[i] < 0)
//       // progect->vectors[i] = progect->vertexes_count + progect->vectors[i];
//     // printf("%d  ", progect->vectors[i]);
//     // if(progect->vectors[i] == 0 || progect->vectors[i] >
//     // progect->vertexes_count) res++;
//   // }
//   // printf("%d\n", res);
//   return res;
// }

/// @brief
/// @param str name if file
/// @param progect final struct
/// @return 0 - all right, 2 - file not found, 3 - wrong file,1 - other error
/// after finctoin need free memory free(progect.vertexes); and
/// free(progect.vectors);
int parser(char* str, arr* progect, minmax_t* frame) {
  int err = 0;
  if (progect != NULL) progect->vertexes_count = 0;
  if (progect != NULL) progect->vectors_count = 0;
  if (progect != NULL) progect->draw_vectors_count = 0;
  if (!str || !progect)
    err = 1;
  else if (variableCount(str, progect))
    err = 2;
  else if (!progect->vertexes_count)
    err = 3;  // wrong file
  else {
    progect->vectors = (int*)calloc(progect->vectors_count * 3, sizeof(int));
    progect->vertexes =
        (double*)calloc(progect->vertexes_count * 3, sizeof(double));
    progect->vecs =
        (double*)calloc((progect->vectors_count * 2) * 3, sizeof(double));
    err = getValue(str, progect);
    if (err) {  // check wrong vectors
      free_arr(progect);
    } else if (progect->vectors != NULL && progect->vertexes != NULL &&
               progect->vecs != NULL) {
      normalization(progect, frame);
      verts4vecs(progect);
    } else
      err = 1;
  }
  //  if (err != 0) free_arr(progect);
  return err;
}

void verts4vecs(arr* progect) {
  int vect = 0;
  for (int i = 0; progect->vectors[vect] != 0; i += 3) {
    int vr = progect->vectors[vect];
    progect->vecs[i] = progect->vertexes[vr * 3 - 3];
    progect->vecs[i + 1] = progect->vertexes[vr * 3 - 2];
    progect->vecs[i + 2] = progect->vertexes[vr * 3 - 1];
    vect++;
  }
  progect->draw_vectors_count = vect + 1;
}

void Moving(arr* progect, double value, char c) {
  int i = 0, j = (c == 'x') ? 0 : (c == 'y') ? 1 : 2;
  while (i < progect->vertexes_count * 3) {
    progect->vertexes[i + j] += value;
    i += 3;
  }
}

void RotateX(arr* progect, double value) {
  if (progect) {
    for (int i = 0; i < progect->vertexes_count * 3; i += 3) {
      double tempY = progect->vertexes[i + 1];
      double tempZ = progect->vertexes[i + 2];
      progect->vertexes[i + 1] = cos(value) * tempY - sin(value) * tempZ;
      progect->vertexes[i + 2] = sin(value) * tempY + cos(value) * tempZ;
    }
  }
}

void RotateY(arr* progect, double value) {
  if (progect) {
    for (int i = 0; i < progect->vertexes_count * 3; i += 3) {
      double tempX = progect->vertexes[i];
      double tempZ = progect->vertexes[i + 2];
      progect->vertexes[i] = cos(value) * tempX - sin(value) * tempZ;
      progect->vertexes[i + 2] = sin(value) * tempX + cos(value) * tempZ;
    }
  }
}

void RotateZ(arr* progect, double value) {
  if (progect) {
    for (int i = 0; i < progect->vertexes_count * 3; i += 3) {
      double tempX = progect->vertexes[i];
      double tempY = progect->vertexes[i + 1];
      progect->vertexes[i] = cos(value) * tempX - sin(value) * tempY;
      progect->vertexes[i + 1] = sin(value) * tempX + cos(value) * tempY;
    }
  }
}

void free_arr(arr* project) {
  if (project->vecs != NULL) free(project->vecs);
  if (project->vertexes != NULL) free(project->vertexes);
  if (project->vectors != NULL) free(project->vectors);
}

// int main() {
// arr progect = {0,0,0,0};
// minmax_t frame = {0,0,0,0,0,0};
// int i = parser("../models/Pyramid.obj", &progect, &frame);
//  printf("%d", i);
// //  printf("v:%df:%d\n\n", progect.vertexes_count, progect.vectors_count);

// //  for(int i = 0;progect.vectors[i]!=0; i++) {
// //        if (i%2==0 && i!=1) printf("\n");
// //           printf("%d/", progect.vectors[i]);
// //  }

// // int vect = 0;
// // for(int i = 0;progect.vectors[vect] != 0; i+=3) {
// //   // int vr = progect.vectors[vect];
// //   // progect.vecs[i] = progect.vertexes[vr*3-3];
// //   // progect.vecs[i+1] = progect.vertexes[vr*3-2];
// //   // progect.vecs[i+2] = progect.vertexes[vr*3-1];
// //   printf("%d:  %lf /%lf /%lf\n",vect, progect.vecs[i], progect.vecs[i+1],
// progect.vecs[i+2]);
// //         vect++;
// // }

// //  progect

// // for(int i = 0;i<progect.vectors_count * 6; i++) {
// //      if (i%3==0 && i!=0){
// //      printf("\n");
// //      vect++;
// //      }
// //   printf("%lf /", progect.vertexes[i]);
// // }
// free(progect.vertexes);
// free(progect.vectors);
// free(progect.vecs);
// }
