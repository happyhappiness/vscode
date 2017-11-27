static int set_option_time(notification_t *n, const char *value) {
  char *endptr = NULL;
  double tmp;

  errno = 0;
  tmp = strtod(value, &endptr);
  if ((errno != 0)         /* Overflow */
      || (endptr == value) /* Invalid string */
      || (endptr == NULL)  /* This should not happen */
      || (*endptr != 0))   /* Trailing chars */
    return -1;

  n->time = DOUBLE_TO_CDTIME_T(tmp);

  return 0;
}