{
  char** new_argv;
  size_t size;
  char* s;
  int i;

  if (argc <= 0)
    return argv;

  /* Save the original pointer to argv.
   * AIX uses argv to read the process name.
   * (Not the memory pointed to by argv[0..n] as on Linux.)
   */
  process_argv = argv;
  process_argc = argc;

  /* Calculate how much memory we need for the argv strings. */
  size = 0;
  for (i = 0; i < argc; i++)
    size += strlen(argv[i]) + 1;

  /* Add space for the argv pointers. */
  size += (argc + 1) * sizeof(char*);

  new_argv = uv__malloc(size);
  if (new_argv == NULL)
    return argv;
  args_mem = new_argv;

  /* Copy over the strings and set up the pointer table. */
  s = (char*) &new_argv[argc + 1];
  for (i = 0; i < argc; i++) {
    size = strlen(argv[i]) + 1;
    memcpy(s, argv[i], size);
    new_argv[i] = s;
    s += size;
  }
  new_argv[i] = NULL;

  return new_argv;
}