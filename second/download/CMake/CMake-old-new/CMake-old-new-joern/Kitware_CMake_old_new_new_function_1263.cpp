int main(int argc, const char* argv[])
{
  int n = 0;
#if 0
    {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    DuplicateHandle(GetCurrentProcess(), out,
                    GetCurrentProcess(), &out, 0, FALSE,
                    DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);
    SetStdHandle(STD_OUTPUT_HANDLE, out);
    }
    {
    HANDLE out = GetStdHandle(STD_ERROR_HANDLE);
    DuplicateHandle(GetCurrentProcess(), out,
                    GetCurrentProcess(), &out, 0, FALSE,
                    DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);
    SetStdHandle(STD_ERROR_HANDLE, out);
    }
#endif
  if(argc == 2)
    {
    n = atoi(argv[1]);
    }
  else if(argc == 3 && strcmp(argv[1], "run") == 0)
    {
    n = atoi(argv[2]);
    }
  /* Check arguments.  */
  if(n >= 1 && n <= 7 && argc == 3)
    {
    /* This is the child process for a requested test number.  */
    switch (n)
      {
      case 1: return test1(argc, argv);
      case 2: return test2(argc, argv);
      case 3: return test3(argc, argv);
      case 4: return test4(argc, argv);
      case 5: return test5(argc, argv);
      case 6: test6(argc, argv); return 0;
      case 7: return test7(argc, argv);
      }
    fprintf(stderr, "Invalid test number %d.\n", n);
    return 1;
    }
  else if(n >= 1 && n <= 7)
    {
    /* This is the parent process for a requested test number.  */
    int states[7] =
    {
      kwsysProcess_State_Exited,
      kwsysProcess_State_Exited,
      kwsysProcess_State_Expired,
      kwsysProcess_State_Exception,
      kwsysProcess_State_Exited,
      kwsysProcess_State_Expired,
      kwsysProcess_State_Exited
    };
    int exceptions[7] =
    {
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_Fault,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None
    };
    int values[7] = {0, 123, 1, 1, 0, 0, 0};
    int outputs[7] = {1, 1, 1, 1, 1, 0, 1};
    int delays[7] = {0, 0, 0, 0, 0, 1, 0};
    double timeouts[7] = {10, 10, 10, 10, 30, 10, -1};
    int polls[7] = {0, 0, 0, 0, 0, 0, 1};
    int repeat[7] = {2, 1, 1, 1, 1, 1, 1};
    int r;
    const char* cmd[4];
#ifdef _WIN32
    char* argv0 = 0;
    if(n == 0 && (argv0 = strdup(argv[0])))
      {
      /* Try converting to forward slashes to see if it works.  */
      char* c;
      for(c=argv0; *c; ++c)
        {
        if(*c == '\\')
          {
          *c = '/';
          }
        }
      cmd[0] = argv0;
      }
    else
      {
      cmd[0] = argv[0];
      }
#else
    cmd[0] = argv[0];
#endif
    cmd[1] = "run";
    cmd[2] = argv[1];
    cmd[3] = 0;
    fprintf(stdout, "Output on stdout before test %d.\n", n);
    fprintf(stderr, "Output on stderr before test %d.\n", n);
    fflush(stdout);
    fflush(stderr);
    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0,
                 outputs[n-1], delays[n-1], timeouts[n-1],
                 polls[n-1], repeat[n-1]);
    fprintf(stdout, "Output on stdout after test %d.\n", n);
    fprintf(stderr, "Output on stderr after test %d.\n", n);
    fflush(stdout);
    fflush(stderr);
#if _WIN32
    if(argv0) { free(argv0); }
#endif
    return r;
    }
  else if(argc > 2 && strcmp(argv[1], "0") == 0)
    {
    /* This is the special debugging test to run a given command
       line.  */
    const char** cmd = argv+2;
    int state = kwsysProcess_State_Exited;
    int exception = kwsysProcess_Exception_None;
    int value = 0;
    double timeout = 0;
    int r = runChild(cmd, state, exception, value, 0, 1, 0, timeout, 0, 1);
    return r;
    }
  else
    {
    /* Improper usage.  */
    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
    return 1;
    }
}