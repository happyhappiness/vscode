      case 4: return test4(argc, argv);
      case 5: return test5(argc, argv);
      case 6: test6(argc, argv); return 0;
      }
    fprintf(stderr, "Invalid test number %d.\n", n);
    return 1;
    }
  
  if(n >= 0 && n <= 6)
    {
    int states[6] =
    {
      kwsysProcess_State_Exited,
      kwsysProcess_State_Exited,
      kwsysProcess_State_Expired,
      kwsysProcess_State_Exception,
      kwsysProcess_State_Exited,
      kwsysProcess_State_Expired
    };
    int exceptions[6] =
    {
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_Fault,
      kwsysProcess_Exception_None,
      kwsysProcess_Exception_None
    };
    int values[6] = {0, 123, 1, 1, 0, 0};
    int outputs[6] = {1, 1, 1, 1, 1, 0};
    int delays[6] = {0, 0, 0, 0, 0, 1};
    double timeouts[6] = {10, 10, 10, 10, 30, 10};
    int r;
    const char* cmd[4];
#ifdef _WIN32
