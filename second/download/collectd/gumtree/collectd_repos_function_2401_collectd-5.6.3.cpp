int parse_values(char *buffer, value_list_t *vl, const data_set_t *ds) {
  size_t i;
  char *dummy;
  char *ptr;
  char *saveptr;

  if ((buffer == NULL) || (vl == NULL) || (ds == NULL))
    return EINVAL;

  i = 0;
  dummy = buffer;
  saveptr = NULL;
  vl->time = 0;
  while ((ptr = strtok_r(dummy, ":", &saveptr)) != NULL) {
    dummy = NULL;

    if (i >= vl->values_len) {
      /* Make sure i is invalid. */
      i = 0;
      break;
    }

    if (vl->time == 0) {
      if (strcmp("N", ptr) == 0)
        vl->time = cdtime();
      else {
        char *endptr = NULL;
        double tmp;

        errno = 0;
        tmp = strtod(ptr, &endptr);
        if ((errno != 0)        /* Overflow */
            || (endptr == ptr)  /* Invalid string */
            || (endptr == NULL) /* This should not happen */
            || (*endptr != 0))  /* Trailing chars */
          return (-1);

        vl->time = DOUBLE_TO_CDTIME_T(tmp);
      }

      continue;
    }

    if ((strcmp("U", ptr) == 0) && (ds->ds[i].type == DS_TYPE_GAUGE))
      vl->values[i].gauge = NAN;
    else if (0 != parse_value(ptr, &vl->values[i], ds->ds[i].type))
      return -1;

    i++;
  } /* while (strtok_r) */

  if ((ptr != NULL) || (i == 0))
    return (-1);
  return (0);
}