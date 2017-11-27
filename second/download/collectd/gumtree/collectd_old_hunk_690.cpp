
  printf("%s: %g average |", status_str, average);
  for (size_t i = 0; i < values_num; i++)
    printf(" %s=%f;;;;", values_names[i], values[i]);
  printf("\n");

  return (status_code);
} /* int do_check_con_average */

static int do_check_con_sum(size_t values_num, double *values,
                            char **values_names) {
  double total;
  int total_num;
