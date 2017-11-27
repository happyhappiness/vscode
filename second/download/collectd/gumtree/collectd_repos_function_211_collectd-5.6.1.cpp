static int flush (lcc_connection_t *c, int argc, char **argv)
{
  int timeout = -1;

  lcc_identifier_t *identifiers = NULL;
  size_t identifiers_num = 0;

  char **plugins = NULL;
  size_t plugins_num = 0;

  int status;

  assert (strcasecmp (argv[0], "flush") == 0);

#define BAIL_OUT(s) \
  do { \
    if (identifiers != NULL) \
      free (identifiers); \
    identifiers_num = 0; \
    if (plugins != NULL) \
      free (plugins); \
    plugins_num = 0; \
    return (s); \
  } while (0)

  for (int i = 1; i < argc; ++i) {
    char *key, *value;

    key   = argv[i];
    value = strchr (argv[i], (int)'=');

    if (! value) {
      fprintf (stderr, "ERROR: flush: Invalid option ``%s''.\n", argv[i]);
      BAIL_OUT (-1);
    }

    *value = '\0';
    ++value;

    if (strcasecmp (key, "timeout") == 0) {
      char *endptr = NULL;

      timeout = (int) strtol (value, &endptr, 0);

      if (endptr == value) {
        fprintf (stderr, "ERROR: Failed to parse timeout as number: %s.\n",
            value);
        BAIL_OUT (-1);
      }
      else if ((endptr != NULL) && (*endptr != '\0')) {
        fprintf (stderr, "WARNING: Ignoring trailing garbage after timeout: "
            "%s.\n", endptr);
      }
    }
    else if (strcasecmp (key, "plugin") == 0) {
      status = array_grow ((void *)&plugins, &plugins_num,
          sizeof (*plugins));
      if (status != 0)
        BAIL_OUT (status);

      plugins[plugins_num - 1] = value;
    }
    else if (strcasecmp (key, "identifier") == 0) {
      status = array_grow ((void *)&identifiers, &identifiers_num,
          sizeof (*identifiers));
      if (status != 0)
        BAIL_OUT (status);

      memset (identifiers + (identifiers_num - 1), 0, sizeof (*identifiers));
      status = parse_identifier (c, value,
          identifiers + (identifiers_num - 1));
      if (status != 0)
        BAIL_OUT (status);
    }
    else {
      fprintf (stderr, "ERROR: flush: Unknown option `%s'.\n", key);
      BAIL_OUT (-1);
    }
  }

  if (plugins_num == 0) {
    status = array_grow ((void *)&plugins, &plugins_num, sizeof (*plugins));
    if (status != 0)
      BAIL_OUT (status);

    assert (plugins_num == 1);
    plugins[0] = NULL;
  }

  for (size_t i = 0; i < plugins_num; ++i) {
    if (identifiers_num == 0) {
      status = lcc_flush (c, plugins[i], NULL, timeout);
      if (status != 0)
        fprintf (stderr, "ERROR: Failed to flush plugin `%s': %s.\n",
            (plugins[i] == NULL) ? "(all)" : plugins[i], lcc_strerror (c));
    }
    else {
      for (size_t j = 0; j < identifiers_num; ++j) {
        status = lcc_flush (c, plugins[i], identifiers + j, timeout);
        if (status != 0) {
          char id[1024];

          lcc_identifier_to_string (c, id, sizeof (id), identifiers + j);
          fprintf (stderr, "ERROR: Failed to flush plugin `%s', "
              "identifier `%s': %s.\n",
              (plugins[i] == NULL) ? "(all)" : plugins[i],
              id, lcc_strerror (c));
        }
      }
    }
  }

  BAIL_OUT (0);
#undef BAIL_OUT
}