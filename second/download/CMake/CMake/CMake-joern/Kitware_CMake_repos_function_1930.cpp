int main(int argc, const char* argv[])
{
  int n = 0;

#ifdef _WIN32
  int i;
  char new_args[10][_MAX_PATH];
  LPWSTR* w_av = CommandLineToArgvW(GetCommandLineW(), &argc);
  for (i = 0; i < argc; i++) {
    kwsysEncoding_wcstombs(new_args[i], w_av[i], _MAX_PATH);
    argv[i] = new_args[i];
  }
  LocalFree(w_av);
#endif

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
  if (argc == 2) {
    n = atoi(argv[1]);
  } else if (argc == 3 && strcmp(argv[1], "run") == 0) {
    n = atoi(argv[2]);
  }
  /* Check arguments.  */
  if (((n >= 1 && n <= 10) || n == 108 || n == 109 || n == 110) && argc == 3) {
    /* This is the child process for a requested test number.  */
    switch (n) {
      case 1:
        return test1(argc, argv);
      case 2:
        return test2(argc, argv);
      case 3:
        return test3(argc, argv);
      case 4:
        return test4(argc, argv);
      case 5:
        return test5(argc, argv);
      case 6:
        test6(argc, argv);
        return 0;
      case 7:
        return test7(argc, argv);
      case 8:
        return test8(argc, argv);
      case 9:
        return test9(argc, argv);
      case 10:
        return test10(argc, argv);
      case 108:
        return test8_grandchild(argc, argv);
      case 109:
        return test9_grandchild(argc, argv);
      case 110:
        return test10_grandchild(argc, argv);
    }
    fprintf(stderr, "Invalid test number %d.\n", n);
    return 1;
  } else if (n >= 1 && n <= 10) {
    /* This is the parent process for a requested test number.  */
    int states[10] = {
      kwsysProcess_State_Exited,   kwsysProcess_State_Exited,
      kwsysProcess_State_Expired,  kwsysProcess_State_Exception,
      kwsysProcess_State_Exited,   kwsysProcess_State_Expired,
      kwsysProcess_State_Exited,   kwsysProcess_State_Exited,
      kwsysProcess_State_Expired,  /* Ctrl+C handler test */
      kwsysProcess_State_Exception /* Process group test */
    };
    int exceptions[10] = {
      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
      kwsysProcess_Exception_None, kwsysProcess_Exception_Fault,
      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
      kwsysProcess_Exception_None, kwsysProcess_Exception_Interrupt
    };
    int values[10] = { 0, 123, 1, 1, 0, 0, 0, 0, 1, 1 };
    int shares[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
    int outputs[10] = { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
    int delays[10] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
    double timeouts[10] = { 10, 10, 10, 30, 30, 10, -1, 10, 6, 4 };
    int polls[10] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
    int repeat[10] = { 257, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int createNewGroups[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
    unsigned int interruptDelays[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 3, 2 };
    int r;
    const char* cmd[4];
#ifdef _WIN32
    char* argv0 = 0;
#endif
    char* test1IterationsStr = getenv("KWSYS_TEST_PROCESS_1_COUNT");
    if (test1IterationsStr) {
      long int test1Iterations = strtol(test1IterationsStr, 0, 10);
      if (test1Iterations > 10 && test1Iterations != LONG_MAX) {
        repeat[0] = (int)test1Iterations;
      }
    }
#ifdef _WIN32
    if (n == 0 && (argv0 = strdup(argv[0]))) {
      /* Try converting to forward slashes to see if it works.  */
      char* c;
      for (c = argv0; *c; ++c) {
        if (*c == '\\') {
          *c = '/';
        }
      }
      cmd[0] = argv0;
    } else {
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
    r = runChild(cmd, states[n - 1], exceptions[n - 1], values[n - 1],
                 shares[n - 1], outputs[n - 1], delays[n - 1], timeouts[n - 1],
                 polls[n - 1], repeat[n - 1], 0, createNewGroups[n - 1],
                 interruptDelays[n - 1]);
    fprintf(stdout, "Output on stdout after test %d.\n", n);
    fprintf(stderr, "Output on stderr after test %d.\n", n);
    fflush(stdout);
    fflush(stderr);
#if defined(_WIN32)
    if (argv0) {
      free(argv0);
    }
#endif
    return r;
  } else if (argc > 2 && strcmp(argv[1], "0") == 0) {
    /* This is the special debugging test to run a given command
       line.  */
    const char** cmd = argv + 2;
    int state = kwsysProcess_State_Exited;
    int exception = kwsysProcess_Exception_None;
    int value = 0;
    double timeout = 0;
    int r =
      runChild(cmd, state, exception, value, 0, 1, 0, timeout, 0, 1, 0, 0, 0);
    return r;
  } else {
    /* Improper usage.  */
    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
    return 1;
  }
}