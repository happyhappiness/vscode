{
  (void)argc; (void)argv;
  fprintf(stdout, "Output before sleep on stdout from timeout test.\n");
  fprintf(stderr, "Output before sleep on stderr from timeout test.\n");
  fflush(stdout);
  fflush(stderr);
  testProcess_sleep(15);
  fprintf(stdout, "Output after sleep on stdout from timeout test.\n");
  fprintf(stderr, "Output after sleep on stderr from timeout test.\n");
  return 0;
}