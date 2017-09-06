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