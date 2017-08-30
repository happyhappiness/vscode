  return 0;
}

int test8(int argc, const char* argv[])
{
  /* Create a disowned grandchild to test handling of processes
     that exit before their children.  */
  int r;
  const char* cmd[4];
  (void)argc;
  cmd[0] = argv[0];
  cmd[1] = "run";
  cmd[2] = "108";
  cmd[3] = 0;
  fprintf(stdout, "Output on stdout before grandchild test.\n");
  fprintf(stderr, "Output on stderr before grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  r = runChild(cmd, kwsysProcess_State_Disowned, kwsysProcess_Exception_None,
               1, 1, 1, 0, 10, 0, 1, 1);
  fprintf(stdout, "Output on stdout after grandchild test.\n");
  fprintf(stderr, "Output on stderr after grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  return r;
}

int test8_grandchild(int argc, const char* argv[])
{
  (void)argc; (void)argv;
  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
  fflush(stdout);
  fflush(stderr);
  /* TODO: Instead of closing pipes here leave them open to make sure
     the grandparent can stop listening when the parent exits.  This
     part of the test cannot be enabled until the feature is
     implemented.  */
  fclose(stdout);
  fclose(stderr);
#if defined(_WIN32)
  Sleep(15000);
#else
  sleep(15);
#endif
  return 0;
}


int runChild2(kwsysProcess* kp,
              const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout,
              int poll, int disown)
{
  int result = 0;
  char* data = 0;
