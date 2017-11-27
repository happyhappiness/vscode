      &ret_values_num, &ret_values, &ret_values_names);
  if (status != 0) {
    fprintf (stderr, "ERROR: %s\n", lcc_strerror (c));
    BAIL_OUT (-1);
  }

  for (size_t i = 0; i < ret_values_num; ++i)
    printf ("%s=%e\n", ret_values_names[i], ret_values[i]);
  BAIL_OUT (0);
#undef BAIL_OUT
} /* getval */

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
