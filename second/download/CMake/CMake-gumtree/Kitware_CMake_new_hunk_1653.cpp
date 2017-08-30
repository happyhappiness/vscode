      case 3: return test3(argc, argv);

      case 4: return test4(argc, argv);

      case 5: return test5(argc, argv);

      case 6: return test6(argc, argv);

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

    int delays[6] = {0, 0, 0, 0, 0, 1};

    double timeouts[6] = {3, 3, 3, 3, 3, 0.1};

    int r;

    const char* cmd[4];

    cmd[0] = argv[0];

