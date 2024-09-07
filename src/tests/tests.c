#include "tests.h"

int main() {
  Suite *viewer_tests[] = {move_x_test(),   move_y_test(),   move_z_test(),
                           scale_test(),    rotate_x_test(), rotate_y_test(),
                           rotate_z_test(), open_test(),     NULL};
  for (int i = 0; viewer_tests[i]; i++) {
    SRunner *sr = srunner_create(viewer_tests[i]);
    srunner_run_all(sr, CK_NORMAL);
    srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  return 0;
}

START_TEST(open) {
  int status = 0;
  arr data_val_1 = {0, 0, 0, 0, 0, 0};
  arr *data_1 = &data_val_1;
  minmax_t miniman_v = {0, 0, 0, 0, 0, 0};
  char path[20] = "test34563456at.obj\0";
  status = parser(path, data_1, &miniman_v);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(move_x) {
  int status = 0;
  arr data_val_1 = {0, 0, 0, 0, 0, 0};
  arr *data_1 = &data_val_1;
  arr data_val_2 = {0, 0, 0, 0, 0, 0};
  arr *data_2 = &data_val_2;
  minmax_t miniman_v = {0, 0, 0, 0, 0, 0};
  status = parser(path, data_1, &miniman_v);
  if (status == 0) status = parser(path, data_2, &miniman_v);
  ck_assert_int_eq(status, 0);
  Moving(data_1, move_arr[_i], 'x');
  for (int i = 0; i < data_1->vertexes_count; i += 3) {
    ck_assert_double_eq(data_1->vertexes[i + 0],
                        (data_2->vertexes[i + 0] + move_arr[_i]));
  }
  free_arr(data_1);
  free_arr(data_2);
}
END_TEST

START_TEST(move_y) {
  int status = 0;
  arr data_val_1 = {0, 0, 0, 0, 0, 0};
  arr *data_1 = &data_val_1;
  arr data_val_2 = {0, 0, 0, 0, 0, 0};
  arr *data_2 = &data_val_2;
  minmax_t miniman_v = {0, 0, 0, 0, 0, 0};
  status = parser(path, data_1, &miniman_v);
  if (status == 0) status = parser(path, data_2, &miniman_v);
  ck_assert_int_eq(status, 0);
  Moving(data_1, move_arr[_i], 'y');
  for (int i = 0; i < data_1->vertexes_count; i += 3) {
    ck_assert_double_eq(data_1->vertexes[i + 1],
                        (data_2->vertexes[i + 1] + move_arr[_i]));
  }
  free_arr(data_1);
  free_arr(data_2);
}
END_TEST

START_TEST(move_z) {
  int status = 0;
  arr data_val_1 = {0, 0, 0, 0, 0, 0};
  arr *data_1 = &data_val_1;
  arr data_val_2 = {0, 0, 0, 0, 0, 0};
  arr *data_2 = &data_val_2;
  minmax_t miniman_v = {0, 0, 0, 0, 0, 0};
  status = parser(path, data_1, &miniman_v);
  if (status == 0) status = parser(path, data_2, &miniman_v);
  ck_assert_int_eq(status, 0);
  Moving(data_1, move_arr[_i], 'z');
  for (int i = 0; i < data_1->vertexes_count; i += 3) {
    ck_assert_double_eq(data_1->vertexes[i + 2],
                        (data_2->vertexes[i + 2] + move_arr[_i]));
  }
  free_arr(data_1);
  free_arr(data_2);
}
END_TEST

START_TEST(scale_arr_test) {
  int status = 0;
  arr data_val_1 = {0, 0, 0, 0, 0, 0};
  arr *data_1 = &data_val_1;
  arr data_val_2 = {0, 0, 0, 0, 0, 0};
  arr *data_2 = &data_val_2;
  minmax_t miniman_v = {0, 0, 0, 0, 0, 0};
  status = parser(path, data_1, &miniman_v);
  if (status == 0) status = parser(path, data_2, &miniman_v);
  ck_assert_int_eq(status, 0);
  scal(&miniman_v, data_1, move_arr[_i]);
  for (int i = 0; i < data_1->vertexes_count; i++) {
    ck_assert_double_eq_tol(data_1->vertexes[i],
                            (data_2->vertexes[i] * 2 * move_arr[_i]), 1e-5);
  }
  free_arr(data_1);
  free_arr(data_2);
}
END_TEST

START_TEST(rotate_x) {
  int status = 0;
  arr data_val_1 = {0, 0, 0, 0, 0, 0};
  arr *data_1 = &data_val_1;
  arr data_val_2 = {0, 0, 0, 0, 0, 0};
  arr *data_2 = &data_val_2;
  minmax_t miniman_v = {0, 0, 0, 0, 0, 0};
  status = parser(path, data_1, &miniman_v);
  ;
  if (status == 0) status = parser(path, data_2, &miniman_v);
  ck_assert_int_eq(status, 0);
  RotateX(data_1, move_arr[_i]);
  for (int i = 0; i < data_1->vertexes_count * 3; i += 3) {
    ck_assert_double_eq(data_1->vertexes[i + 0], data_2->vertexes[i + 0]);
    ck_assert_double_eq(data_1->vertexes[i + 1],
                        (data_2->vertexes[i + 1] * cos(move_arr[_i]) -
                         data_2->vertexes[i + 2] * sin(move_arr[_i])));
    ck_assert_double_eq(data_1->vertexes[i + 2],
                        (data_2->vertexes[i + 2] * cos(move_arr[_i]) +
                         data_2->vertexes[i + 1] * sin(move_arr[_i])));
  }
  free_arr(data_1);
  free_arr(data_2);
}
END_TEST

START_TEST(rotate_y) {
  int status = 0;
  arr data_val_1 = {0, 0, 0, 0, 0, 0};
  arr *data_1 = &data_val_1;
  arr data_val_2 = {0, 0, 0, 0, 0, 0};
  arr *data_2 = &data_val_2;
  minmax_t miniman_v = {0, 0, 0, 0, 0, 0};
  status = parser(path, data_1, &miniman_v);
  ;
  if (status == 0) status = parser(path, data_2, &miniman_v);
  ck_assert_int_eq(status, 0);
  RotateY(data_1, move_arr[_i]);
  for (int i = 0; i < data_1->vertexes_count * 3; i += 3) {
    ck_assert_double_eq(data_1->vertexes[i + 0],
                        (data_2->vertexes[i + 0] * cos(move_arr[_i]) -
                         data_2->vertexes[i + 2] * sin(move_arr[_i])));
    ck_assert_double_eq(data_1->vertexes[i + 1], (data_2->vertexes[i + 1]));
    ck_assert_double_eq(data_1->vertexes[i + 2],
                        (data_2->vertexes[i + 2] * cos(move_arr[_i]) +
                         data_2->vertexes[i + 0] * sin(move_arr[_i])));
  }
  free_arr(data_1);
  free_arr(data_2);
}
END_TEST

START_TEST(rotate_z) {
  int status = 0;
  arr data_val_1 = {0, 0, 0, 0, 0, 0};
  arr *data_1 = &data_val_1;
  arr data_val_2 = {0, 0, 0, 0, 0, 0};
  arr *data_2 = &data_val_2;
  minmax_t miniman_v = {0, 0, 0, 0, 0, 0};
  status = parser(path, data_1, &miniman_v);
  ;
  if (status == 0) status = parser(path, data_2, &miniman_v);
  ck_assert_int_eq(status, 0);
  RotateZ(data_1, move_arr[_i]);
  for (int i = 0; i < data_1->vertexes_count * 3; i += 3) {
    ck_assert_double_eq(data_1->vertexes[i + 0],
                        (data_2->vertexes[i + 0] * cos(move_arr[_i]) -
                         data_2->vertexes[i + 1] * sin(move_arr[_i])));
    ck_assert_double_eq(data_1->vertexes[i + 1],
                        (data_2->vertexes[i + 1] * cos(move_arr[_i]) +
                         data_2->vertexes[i + 0] * sin(move_arr[_i])));
    ck_assert_double_eq(data_1->vertexes[i + 2], data_2->vertexes[i + 2]);
  }
  free_arr(data_1);
  free_arr(data_2);
}
END_TEST

Suite *move_x_test() {
  Suite *s = suite_create("\033[42m-=3D_TESTS_MOVE_X=-\033[0m");
  TCase *tc = tcase_create("3D_TESTS_MOVE_X");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, move_x, 0, 13);
  return s;
}

Suite *move_y_test() {
  Suite *s = suite_create("\033[42m-=3D_TESTS_MOVE_Y=-\033[0m");
  TCase *tc = tcase_create("3D_TESTS_MOVE_Y");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, move_y, 0, 13);
  return s;
}

Suite *move_z_test() {
  Suite *s = suite_create("\033[42m-=3D_TESTS_MOVE_Z=-\033[0m");
  TCase *tc = tcase_create("3D_TESTS_MOVE_Z");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, move_z, 0, 13);
  return s;
}

Suite *scale_test() {
  Suite *s = suite_create("\033[42m-=3D_TESTS_SCALE=-\033[0m");
  TCase *tc = tcase_create("3D_TESTS_SCALE");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, scale_arr_test, 0, 13);
  return s;
}

Suite *rotate_x_test() {
  Suite *s = suite_create("\033[42m-=3D_TESTS_ROTATE_X=-\033[0m");
  TCase *tc = tcase_create("3D_TESTS_ROTATE_X");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, rotate_x, 0, 13);
  return s;
}

Suite *rotate_y_test() {
  Suite *s = suite_create("\033[42m-=3D_TESTS_ROTATE_Y=-\033[0m");
  TCase *tc = tcase_create("3D_TESTS_ROTATE_Y");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, rotate_y, 0, 13);
  return s;
}

Suite *rotate_z_test() {
  Suite *s = suite_create("\033[42m-=3D_TESTS_ROTATE_Z=-\033[0m");
  TCase *tc = tcase_create("3D_TESTS_ROTATE_Z");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, rotate_z, 0, 13);
  return s;
}

Suite *open_test() {
  Suite *s = suite_create("\033[42m-=3D_TESTS_OPEN=-\033[0m");
  TCase *tc = tcase_create("3D_TESTS_OPEN");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, open);
  return s;
}