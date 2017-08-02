{
  /* The grandchild just sleeps for a few seconds and handles signals.  */
  (void)argc; (void)argv;
  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
  fflush(stdout);
  fflush(stderr);
  /* Sleep for 6 seconds.  */
  testProcess_sleep(6);
  fprintf(stdout, "Output on stdout from grandchild after sleep.\n");
  fprintf(stderr, "Output on stderr from grandchild after sleep.\n");
  fflush(stdout);
  fflush(stderr);
  return 0;
}