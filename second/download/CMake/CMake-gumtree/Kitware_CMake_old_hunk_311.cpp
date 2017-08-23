
static int test8_grandchild(int argc, const char* argv[])
{
  (void)argc; (void)argv;
  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
  fflush(stdout);
