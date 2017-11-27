
  assert(strcasecmp(argv[0], "putval") == 0);

  if (argc < 3) {
    fprintf(stderr, "ERROR: putval: Missing identifier "
                    "and/or value list.\n");
    return (-1);
  }

  vl.values = values;
  vl.values_types = values_types;

  status = parse_identifier(c, argv[1], &vl.identifier);
  if (status != 0)
    return (status);

  for (int i = 2; i < argc; ++i) {
    char *tmp;

    tmp = strchr(argv[i], (int)'=');

