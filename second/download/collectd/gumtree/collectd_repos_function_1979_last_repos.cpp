static int set_option(value_list_t *vl, const char *key, const char *value) {
  if ((vl == NULL) || (key == NULL) || (value == NULL))
    return -1;

  if (strcasecmp("interval", key) == 0) {
    double tmp;
    char *endptr;

    endptr = NULL;
    errno = 0;
    tmp = strtod(value, &endptr);

    if ((errno == 0) && (endptr != NULL) && (endptr != value) && (tmp > 0.0))
      vl->interval = DOUBLE_TO_CDTIME_T(tmp);
  } else
    return 1;

  return 0;
}