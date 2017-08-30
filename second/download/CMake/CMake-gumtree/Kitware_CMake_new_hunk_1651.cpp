  fflush(stdout);
  fflush(stderr);
  r = runChild(cmd, kwsysProcess_State_Exception,
               kwsysProcess_Exception_Fault, 1, 1, 0, 2);
  fprintf(stdout, "Output on stdout after recursive test.\n");
  fprintf(stderr, "Output on stderr after recursive test.\n");
  fflush(stdout);
  fflush(stderr);
  return r;
}

#define TEST6_SIZE (4096*2)
int test6(int argc, const char* argv[])
{
  int i;
  char runaway[TEST6_SIZE+2];
  (void)argc; (void)argv;
  for(i=0;i < TEST6_SIZE;++i)
    {
    runaway[i] = '.';
    }
  runaway[TEST6_SIZE] = '\n';
  runaway[TEST6_SIZE] = 0;

  /* Generate huge amounts of output to test killing.  */
  for(;;)
    {
    fwrite(runaway, 1, TEST6_SIZE+2, stdout);
    fflush(stdout);
    }
  return 0;
}


int runChild(const char* cmd[], int state, int exception, int value,
             int share, int delay, double timeout)
{
  int result = 0;
  char* data = 0;
