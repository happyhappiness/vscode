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

static int runChild2(kwsysProcess* kp,
              const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout,
              int poll, int disown)
{
  int result = 0;
  char* data = 0;
