      case 6: test6(argc, argv); return 0;

      case 7: return test7(argc, argv);

      case 8: return test8(argc, argv);

      case 9: return test9(argc, argv);

      case 10: return test10(argc, argv);

      case 108: return test8_grandchild(argc, argv);

      case 109: return test9_grandchild(argc, argv);

      case 110: return test10_grandchild(argc, argv);

      }

    fprintf(stderr, "Invalid test number %d.\n", n);

    return 1;

    }

  else if(n >= 1 && n <= 10)

    {

    /* This is the parent process for a requested test number.  */

    int states[10] =

    {

      kwsysProcess_State_Exited,

      kwsysProcess_State_Exited,

