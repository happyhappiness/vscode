static int num_compare(const int *a, const int *b) {
  assert((a != NULL) && (b != NULL));
  if (*a < *b)
    return -1;
  else if (*a > *b)
    return 1;
  else
    return 0;
}