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
