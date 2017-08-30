             int share, int output, int delay, double timeout, int poll,

             int repeat, int disown);



int test1(int argc, const char* argv[])

{

  (void)argc; (void)argv;

  fprintf(stdout, "Output on stdout from test returning 0.\n");

  fprintf(stderr, "Output on stderr from test returning 0.\n");

  return 0;

}



int test2(int argc, const char* argv[])

{

  (void)argc; (void)argv;

  fprintf(stdout, "Output on stdout from test returning 123.\n");

  fprintf(stderr, "Output on stderr from test returning 123.\n");

  return 123;

}



int test3(int argc, const char* argv[])

{

  (void)argc; (void)argv;

  fprintf(stdout, "Output before sleep on stdout from timeout test.\n");

