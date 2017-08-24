  return 0;
}

/* Quick hack to test grandchild killing.  */
/*#define TEST5_GRANDCHILD_KILL*/
#ifdef TEST5_GRANDCHILD_KILL
# define TEST5_TIMEOUT 10
#else
# define TEST5_TIMEOUT 30
#endif

int test5(int argc, const char* argv[])
{
  int r;
  const char* cmd[4];
  (void)argc;
  cmd[0] = argv[0];
  cmd[1] = "run";
#ifdef TEST5_GRANDCHILD_KILL
  cmd[2] = "3";
#else
  cmd[2] = "4";
#endif
  cmd[3] = 0;
  fprintf(stdout, "Output on stdout before recursive test.\n");
  fprintf(stderr, "Output on stderr before recursive test.\n");
  fflush(stdout);
  fflush(stderr);
  r = runChild(cmd, kwsysProcess_State_Exception,
               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0, 1);
  fprintf(stdout, "Output on stdout after recursive test.\n");
  fprintf(stderr, "Output on stderr after recursive test.\n");
  fflush(stdout);
