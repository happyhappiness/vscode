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
  else if(argc == 3)
    {
    n = atoi(argv[2]);
    }
  /* Check arguments.  */
  if(n < 1 || n > 5 || (argc == 3 && strcmp(argv[1], "run") != 0))
    {
    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
    return 1;
    }
  if(argc == 3)
    {
    switch (n)
      {
      case 1: return test1(argc, argv);
      case 2: return test2(argc, argv);
      case 3: return test3(argc, argv);
      case 4: return test4(argc, argv);
      case 5: return test5(argc, argv);
      }
    fprintf(stderr, "Invalid test number %d.\n", n);
    return 1;
    }
  
  if(n >= 0 && n <= 5)
    {
    int states[5] =
    {
      kwsysProcess_State_Exited,
      kwsysProcess_State_Exited,
      kwsysProcess_State_Expired,
      kwsysProcess_State_Exception,
      kwsysProcess_State_Exited
    };
    int exceptions[5] =
    {
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_Fault,
      kwsysProcess_Exception_None
    };
    int values[5] = {0, 123, 1, 1, 0};
    int r;
    const char* cmd[4];
    cmd[0] = argv[0];
    cmd[1] = "run";
    cmd[2] = argv[1];
    cmd[3] = 0;
    fprintf(stdout, "Output on stdout before test %d.\n", n);
    fprintf(stderr, "Output on stderr before test %d.\n", n);
    fflush(stdout);
    fflush(stderr);
    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0, 3);
    fprintf(stdout, "Output on stdout after test %d.\n", n);
    fprintf(stderr, "Output on stderr after test %d.\n", n);
    fflush(stdout);
    fflush(stderr);
    return r;
    }
  else
    {
    fprintf(stderr, "Test number out of range\n");
    return 1;
    }  
}