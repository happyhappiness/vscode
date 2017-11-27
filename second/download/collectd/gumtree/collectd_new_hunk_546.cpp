
  size_t   ret_values_num   = 0;
  gauge_t *ret_values       = NULL;
  char   **ret_values_names = NULL;

  int status;

  assert (strcasecmp (argv[0], "getval") == 0);

  if (argc != 2) {
    fprintf (stderr, "ERROR: getval: Missing identifier.\n");
    return (-1);
  }

  status = parse_identifier (c, argv[1], &ident);
  if (status != 0)
    return (status);

#define BAIL_OUT(s) \
  do { \
    if (ret_values != NULL) \
      free (ret_values); \
    if (ret_values_names != NULL) { \
      for (size_t i = 0; i < ret_values_num; ++i) \
        free (ret_values_names[i]); \
      free (ret_values_names); \
    } \
    ret_values_num = 0; \
    return (s); \
  } while (0)
