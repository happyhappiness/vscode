    fprintf(stderr, "Output on stderr before test %d.\n", n);

    fflush(stdout);

    fflush(stderr);

    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], shares[n-1],

                 outputs[n-1], delays[n-1], timeouts[n-1],

                 polls[n-1], repeat[n-1], 0, createNewGroups[n-1],

                 interruptDelays[n-1]);

    fprintf(stdout, "Output on stdout after test %d.\n", n);

    fprintf(stderr, "Output on stderr after test %d.\n", n);

    fflush(stdout);

    fflush(stderr);

#if defined(_WIN32)

    if(argv0) { free(argv0); }

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

    int r = runChild(cmd, state, exception, value, 0, 1, 0, timeout,

      0, 1, 0, 0, 0);

    return r;

    }

  else

    {

    /* Improper usage.  */

    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);

    return 1;

    }

}
