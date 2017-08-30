     implemented.  */
  fclose(stdout);
  fclose(stderr);
  testProcess_sleep(15);
  return 0;
}

static int test9(int argc, const char* argv[])
{
  /* Test Ctrl+C behavior: the root test program will send a Ctrl+C to this
     process.  Here, we start a child process that sleeps for a long time
     while ignoring signals.  The test is successful if this process waits
     for the child to return before exiting from the Ctrl+C handler.

     WARNING:  This test will falsely pass if the share parameter of runChild
     was set to 0 when invoking the test9 process.  */
  int r;
  const char* cmd[4];
  (void)argc;
  cmd[0] = argv[0];
  cmd[1] = "run";
  cmd[2] = "109";
  cmd[3] = 0;
  fprintf(stdout, "Output on stdout before grandchild test.\n");
  fprintf(stderr, "Output on stderr before grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  r = runChild(cmd, kwsysProcess_State_Exited,
               kwsysProcess_Exception_None,
               0, 1, 1, 0, 30, 0, 1, 0, 0, 0);
  /* This sleep will avoid a race condition between this function exiting
     normally and our Ctrl+C handler exiting abnormally after the process
     exits.  */
  testProcess_sleep(1);
  fprintf(stdout, "Output on stdout after grandchild test.\n");
  fprintf(stderr, "Output on stderr after grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  return r;
}

#if defined(_WIN32)
static BOOL WINAPI test9_grandchild_handler(DWORD dwCtrlType)
{
  /* Ignore all Ctrl+C/Break signals.  We must use an actual handler function
     instead of using SetConsoleCtrlHandler(NULL, TRUE) so that we can also
     ignore Ctrl+Break in addition to Ctrl+C.  */
  (void)dwCtrlType;
  return TRUE;
}
#endif

static int test9_grandchild(int argc, const char* argv[])
{
  /* The grandchild just sleeps for a few seconds while ignoring signals.  */
  (void)argc; (void)argv;
#if defined(_WIN32)
  if(!SetConsoleCtrlHandler(test9_grandchild_handler, TRUE))
    {
    return 1;
    }
#else
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  if(sigaction(SIGINT, &sa, 0) < 0)
    {
    return 1;
    }
#endif
  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
  fflush(stdout);
  fflush(stderr);
  /* Sleep for 9 seconds.  */
  testProcess_sleep(9);
  fprintf(stdout, "Output on stdout from grandchild after sleep.\n");
  fprintf(stderr, "Output on stderr from grandchild after sleep.\n");
  fflush(stdout);
  fflush(stderr);
  return 0;
}

static int test10(int argc, const char* argv[])
{
  /* Test Ctrl+C behavior: the root test program will send a Ctrl+C to this
     process.  Here, we start a child process that sleeps for a long time and
     processes signals normally.  However, this grandchild is created in a new
     process group - ensuring that Ctrl+C we receive is sent to our process
     groups.  We make sure it exits anyway.  */
  int r;
  const char* cmd[4];
  (void)argc;
  cmd[0] = argv[0];
  cmd[1] = "run";
  cmd[2] = "110";
  cmd[3] = 0;
  fprintf(stdout, "Output on stdout before grandchild test.\n");
  fprintf(stderr, "Output on stderr before grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  r = runChild(cmd, kwsysProcess_State_Exception,
               kwsysProcess_Exception_Interrupt,
               0, 1, 1, 0, 30, 0, 1, 0, 1, 0);
  fprintf(stdout, "Output on stdout after grandchild test.\n");
  fprintf(stderr, "Output on stderr after grandchild test.\n");
  fflush(stdout);
  fflush(stderr);
  return r;
}

static int test10_grandchild(int argc, const char* argv[])
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

static int runChild2(kwsysProcess* kp,
              const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout,
              int poll, int disown, int createNewGroup,
              unsigned int interruptDelay)
{
  int result = 0;
  char* data = 0;
