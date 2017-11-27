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
