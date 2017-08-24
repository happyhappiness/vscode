# include <unistd.h>
#endif

int test1()
{
  fprintf(stdout, "Output on stdout from test returning 0.\n");
  fprintf(stderr, "Output on stderr from test returning 0.\n");
  return 0;
}

int test2()
{
  fprintf(stdout, "Output on stdout from test returning 123.\n");
  fprintf(stderr, "Output on stderr from test returning 123.\n");
  return 123;
}

int test3()
{
  fprintf(stdout, "Output before sleep on stdout from timeout test.\n");
  fprintf(stderr, "Output before sleep on stderr from timeout test.\n");
  fflush(stdout);
