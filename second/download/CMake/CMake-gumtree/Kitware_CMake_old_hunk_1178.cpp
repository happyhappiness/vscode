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
    double timeouts[7] = {10, 10, 10, 10, TEST5_TIMEOUT, 10, -1};
    int polls[7] = {0, 0, 0, 0, 0, 0, 1};
    int repeat[7] = {2, 1, 1, 1, 1, 1, 1};
    int r;
    const char* cmd[4];
#ifdef _WIN32
