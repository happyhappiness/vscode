static cdtime_t parse_time(char const *tbuf) {
  double t;
  char *endptr = NULL;

  errno = 0;
  t = strtod(tbuf, &endptr);
  if ((errno != 0) || (endptr == NULL) || (endptr[0] != 0))
    return cdtime();

  return DOUBLE_TO_CDTIME_T(t);
}