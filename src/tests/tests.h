#ifndef TESTS_H
#define TESTS_H

#include <check.h>

#include "../back/parser.h"
#define S21_NAN 0.0 / 0.0
Suite *move_x_test();
Suite *move_y_test();
Suite *move_z_test();
Suite *scale_test();
Suite *rotate_x_test();
Suite *rotate_y_test();
Suite *rotate_z_test();
Suite *open_test();
static double move_arr[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 22.2, 33.3, 44.4};
char *path = "models/cat.obj\0";

#endif  // TESTS_H