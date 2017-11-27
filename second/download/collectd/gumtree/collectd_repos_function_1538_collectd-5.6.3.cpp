static int rrd_compare_numeric(const void *a_ptr, const void *b_ptr) {
  int a = *((int *)a_ptr);
  int b = *((int *)b_ptr);

  if (a < b)
    return (-1);
  else if (a > b)
    return (1);
  else
    return (0);
}