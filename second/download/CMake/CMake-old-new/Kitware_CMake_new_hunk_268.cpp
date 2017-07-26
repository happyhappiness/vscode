#define MAXPOLL 20
static int test7(int argc, const char* argv[])
{
  (void)argc;
  (void)argv;
  fprintf(stdout, "Output on stdout before sleep.\n");
  fprintf(stderr, "Output on stderr before sleep.\n");
  fflush(stdout);
