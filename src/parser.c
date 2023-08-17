#include "parser.h"

/// @brief for correct allocted memory culc next size of arrays
/// @return 0 if all right, 2 if file not found

int variableCount(char* str, data* progect) {
  FILE* fp = NULL;
  fp = fopen(str, "r");
  if (!fp) return 2;
  char* line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ') progect->vertexes_count++;
    if (line[0] == 'f' && line[1] == ' ')
      for (size_t i = 1; i < len; i++)
        if (line[i] == ' ' && line[i-1] != ' ') progect->vecotrs_count++;
  }
  free(line);
  fclose(fp);
  return 0;
}


int getValue(char* str, data* progect) {
  FILE* fp = NULL;
  fp = fopen(str, "r");
  if (!fp) return 2;
  char* line = NULL;
  size_t len = 0;
  int i = 0, j = 0;
  while (getline(&line, &len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ') {
      char* cur_line = line;
      char* token = strtok(cur_line, " ");
      while(token != NULL) {
        token = strtok(NULL, " ");
        if(token)
          progect->vertexes[i++] = atof(token);
      }
    } 
    if (line[0] == 'f' && line[1] == ' ') {
      char* cur_line = line;
      char* token = strtok(cur_line, " ");
        int buffer_first_vector = 0;
        int flag_first = 0;
      while(token != NULL) {
        token = strtok(NULL, " ");
        if(token){
          progect->vectors[j++] = atoi(token);
          if(!flag_first) {
            buffer_first_vector = atoi(token);
            flag_first++;
          } else
          progect->vectors[j++] = atoi(token);
        }
      }
      progect->vectors[j++] = buffer_first_vector;
    }
  }
  free(line);
  fclose(fp);
  return 0;
}



minmax_t getMinMax(data progect) {
  minmax_t frame = {0.0,0.0,0.0,0.0,0.0,0.0};
  frame.x_max = frame.x_min = progect.vertexes[0];
  frame.y_max = frame.y_min = progect.vertexes[1];
  frame.z_max = frame.z_min = progect.vertexes[2];
  for (int i = 3; i < progect.vertexes_count*3; i++) {
    if(!(i%3)){
      if(progect.vertexes[i] > frame.x_max) frame.x_max = progect.vertexes[i];
      if(progect.vertexes[i] < frame.x_min) frame.x_min = progect.vertexes[i];
    } else if (i%3 == 1){
      if(progect.vertexes[i] > frame.y_max) frame.y_max = progect.vertexes[i];
      if(progect.vertexes[i] < frame.y_min) frame.y_min = progect.vertexes[i];
    } else {
      if(progect.vertexes[i] > frame.z_max) frame.z_max = progect.vertexes[i];
      if(progect.vertexes[i] < frame.z_min) frame.z_min = progect.vertexes[i];
    } 
  }
  return frame;
}




/// @brief
/// @param str name if file
/// @param progect final struct
/// @return 0 - all right, 2 - file not found, 1 - other error
/// after finctoin need free memory free(progect.vertexes); and free(progect.vectors);


int parser(char* str, data* progect) {
  if (!str || !progect) return 1;
  if (variableCount(str, progect)) return 2;
  progect->vertexes = calloc(progect->vertexes_count * 3, sizeof(double));
  progect->vectors = calloc(progect->vecotrs_count * 2, sizeof(int));
  getValue(str, progect);
  minmax_t frame = getMinMax(*progect);
  printf("%lf   %lf", frame.x_max, frame.y_min);
  return 0;
}

int main() {
  data progect = {0,0,0,0};
  parser("../models/cube.obj", &progect);
  // printf("v:%df:%d\n\n", progect.vertexes_count, progect.vecotrs_count);

  // for(int i = 0; i < progect.vecotrs_count * 2; i++) {
  //   printf("%d  ", progect.vectors[i]);
  // }
  
  free(progect.vertexes);
  free(progect.vectors);
}