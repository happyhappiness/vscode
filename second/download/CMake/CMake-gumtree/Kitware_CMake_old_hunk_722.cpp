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

