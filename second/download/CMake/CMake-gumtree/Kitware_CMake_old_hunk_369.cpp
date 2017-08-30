static int test10_grandchild(int argc, const char* argv[])
{
  /* The grandchild just sleeps for a few seconds and handles signals.  */
  (void)argc; (void)argv;
  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
  fflush(stdout);
