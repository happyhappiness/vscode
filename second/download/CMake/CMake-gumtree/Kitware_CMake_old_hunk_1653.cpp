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

