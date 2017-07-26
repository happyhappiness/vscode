     If you have problems with this test timing out on your system, or want to
     run more than 257 iterations, you can change the number of iterations by
     setting the KWSYS_TEST_PROCESS_1_COUNT environment variable.  */
  (void)argc;
  (void)argv;
  fprintf(stdout, "Output on stdout from test returning 0.\n");
  fprintf(stderr, "Output on stderr from test returning 0.\n");
  return 0;
}

static int test2(int argc, const char* argv[])
{
  (void)argc;
  (void)argv;
  fprintf(stdout, "Output on stdout from test returning 123.\n");
  fprintf(stderr, "Output on stderr from test returning 123.\n");
  return 123;
}

static int test3(int argc, const char* argv[])
{
  (void)argc;
  (void)argv;
  fprintf(stdout, "Output before sleep on stdout from timeout test.\n");
  fprintf(stderr, "Output before sleep on stderr from timeout test.\n");
  fflush(stdout);
