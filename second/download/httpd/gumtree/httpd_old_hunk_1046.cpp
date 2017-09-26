  }

/* If no file name, a single regex must be given inline */

else
  {
  if (i >= argc) return usage(0);
  pattern_list[0] = pcre_compile(argv[i++], options, &error, &errptr, NULL);
  if (pattern_list[0] == NULL)
    {
    fprintf(stderr, "pcregrep: Error in regex at offset %d: %s\n", errptr,
      error);
    return 2;
