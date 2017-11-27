static int putval (lcc_connection_t *c, int argc, char **argv)
{
  lcc_value_list_t vl = LCC_VALUE_LIST_INIT;

  /* 64 ought to be enough for anybody ;-) */
  value_t values[64];
  int     values_types[64];
  size_t  values_len = 0;

  int status;
  int i;

  assert (strcasecmp (argv[0], "putval") == 0);

  if (argc < 3) {
    fprintf (stderr, "ERROR: putval: Missing identifier "
        "and/or value list.\n");
    return (-1);
  }

  vl.values       = values;
  vl.values_types = values_types;

  status = parse_identifier (c, argv[1], &vl.identifier);
  if (status != 0)
    return (status);

  for (i = 2; i < argc; ++i) {
    char *tmp;

    tmp = strchr (argv[i], (int)'=');

    if (tmp != NULL) { /* option */
      char *key   = argv[i];
      char *value = tmp;

      *value = '\0';
      ++value;

      if (strcasecmp (key, "interval") == 0) {
        char *endptr;

        vl.interval = strtol (value, &endptr, 0);

        if (endptr == value) {
          fprintf (stderr, "ERROR: Failed to parse interval as number: %s.\n",
              value);
          return (-1);
        }
        else if ((endptr != NULL) && (*endptr != '\0')) {
          fprintf (stderr, "WARNING: Ignoring trailing garbage after "
              "interval: %s.\n", endptr);
        }
      }
      else {
        fprintf (stderr, "ERROR: putval: Unknown option `%s'.\n", key);
        return (-1);
      }
    }
    else { /* value list */
      char *value;

      tmp = strchr (argv[i], (int)':');

      if (tmp == NULL) {
        fprintf (stderr, "ERROR: putval: Invalid value list: %s.\n",
            argv[i]);
        return (-1);
      }

      *tmp = '\0';
      ++tmp;

      if (strcasecmp (argv[i], "N") == 0) {
        vl.time = 0;
      }
      else {
        char *endptr;

        vl.time = strtol (argv[i], &endptr, 0);

        if (endptr == argv[i]) {
          fprintf (stderr, "ERROR: Failed to parse time as number: %s.\n",
              argv[i]);
          return (-1);
        }
        else if ((endptr != NULL) && (*endptr != '\0')) {
          fprintf (stderr, "ERROR: Garbage after time: %s.\n", endptr);
          return (-1);
        }
      }

      values_len = 0;
      value = tmp;
      while (value != 0) {
        char *dot, *endptr;

        tmp = strchr (argv[i], (int)':');

        if (tmp != NULL) {
          *tmp = '\0';
          ++tmp;
        }

        /* This is a bit of a hack, but parsing types.db just does not make
         * much sense imho -- the server might have different types defined
         * anyway. Also, lcc uses the type information for formatting the
         * number only, so the real meaning does not matter. -tokkee */
        dot = strchr (value, (int)'.');
        endptr = NULL;
        if (strcasecmp (value, "U") == 0) {
          values[values_len].gauge = NAN;
          values_types[values_len] = LCC_TYPE_GAUGE;
        }
        else if (dot) { /* floating point value */
          values[values_len].gauge = strtod (value, &endptr);
          values_types[values_len] = LCC_TYPE_GAUGE;
        }
        else { /* integer */
          values[values_len].counter = strtol (value, &endptr, 0);
          values_types[values_len] = LCC_TYPE_COUNTER;
        }
        ++values_len;

        if (endptr == value) {
          fprintf (stderr, "ERROR: Failed to parse value as number: %s.\n",
              argv[i]);
          return (-1);
        }
        else if ((endptr != NULL) && (*endptr != '\0')) {
          fprintf (stderr, "ERROR: Garbage after value: %s.\n", endptr);
          return (-1);
        }

        value = tmp;
      }

      assert (values_len >= 1);
      vl.values_len = values_len;

      status = lcc_putval (c, &vl);
      if (status != 0) {
        fprintf (stderr, "ERROR: %s\n", lcc_strerror (c));
        return (-1);
      }
    }
  }

  if (values_len == 0) {
    fprintf (stderr, "ERROR: putval: Missing value list(s).\n");
    return (-1);
  }
  return (0);
}