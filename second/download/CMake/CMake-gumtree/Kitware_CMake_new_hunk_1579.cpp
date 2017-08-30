    }
}

/* Define MINPOLL to be one more than the number of times output is
   written.  Define MAXPOLL to be the largest number of times a loop
   delaying 1/10th of a second should ever have to poll.  */
#define MINPOLL 5
#define MAXPOLL 20
int test7(int argc, const char* argv[])
{
  (void)argc; (void)argv;
  fprintf(stdout, "Output on stdout before sleep.\n");
  fprintf(stderr, "Output on stderr before sleep.\n");
  fflush(stdout);
  fflush(stderr);
  /* Sleep for 1 second.  */
#if defined(_WIN32)
  Sleep(1000);
#else
  usleep(1000000);
#endif
  fprintf(stdout, "Output on stdout after sleep.\n");
  fprintf(stderr, "Output on stderr after sleep.\n");
  fflush(stdout);
  fflush(stderr);
  return 0;
}

int runChild(const char* cmd[], int state, int exception, int value,
             int share, int output, int delay, double timeout,
             int poll)
{
  int result = 0;
  char* data = 0;
  int length = 0;
  double userTimeout = 0;
  double* pUserTimeout = 0;
  kwsysProcess* kp = kwsysProcess_New();
  if(!kp)
    {
