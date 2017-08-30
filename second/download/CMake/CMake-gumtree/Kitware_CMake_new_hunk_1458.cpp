      case 5: return test5(argc, argv);

      case 6: test6(argc, argv); return 0;

      case 7: return test7(argc, argv);

      case 8: return test8(argc, argv);

      case 108: return test8_grandchild(argc, argv);

      }

    fprintf(stderr, "Invalid test number %d.\n", n);

    return 1;

    }

  else if(n >= 1 && n <= 8)

    {

    /* This is the parent process for a requested test number.  */

    int states[8] =

    {

      kwsysProcess_State_Exited,

      kwsysProcess_State_Exited,

      kwsysProcess_State_Expired,

      kwsysProcess_State_Exception,

      kwsysProcess_State_Exited,

      kwsysProcess_State_Expired,

      kwsysProcess_State_Exited,

      kwsysProcess_State_Exited

    };

    int exceptions[8] =

    {

      kwsysProcess_Exception_None,

      kwsysProcess_Exception_None,

      kwsysProcess_Exception_None,

      kwsysProcess_Exception_Fault,

      kwsysProcess_Exception_None,

      kwsysProcess_Exception_None,

      kwsysProcess_Exception_None,

      kwsysProcess_Exception_None

    };

    int values[8] = {0, 123, 1, 1, 0, 0, 0, 0};

    int outputs[8] = {1, 1, 1, 1, 1, 0, 1, 1};

    int delays[8] = {0, 0, 0, 0, 0, 1, 0, 0};

    double timeouts[8] = {10, 10, 10, 10, 30, 10, -1, 10};

    int polls[8] = {0, 0, 0, 0, 0, 0, 1, 0};

    int repeat[8] = {2, 1, 1, 1, 1, 1, 1, 1};

    int r;

    const char* cmd[4];

#ifdef _WIN32

