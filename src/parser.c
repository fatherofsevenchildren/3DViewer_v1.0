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
        if (line[i] == ' ' && line[i-1] != ' ') progect->vercotrs_count++;
  }
  free(line);
  return 0;
}

/// @brief
/// @param str name if file
/// @param progect final struct
/// @return 0 - all right, 2 - file not found, 1 - other error

int parser(char* str, data* progect) {
  if (!str || !progect) return 1;
  variableCount(str, progect);
  return 0;
}

int main() {
  data progect;
  parser("../models/cube.obj", &progect);
  printf("v:%df:%d", progect.vertexes_count, progect.vercotrs_count);
}