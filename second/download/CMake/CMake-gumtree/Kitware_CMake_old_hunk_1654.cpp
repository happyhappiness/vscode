    fprintf(stderr, "Output on stderr before test %d.\n", n);

    fflush(stdout);

    fflush(stderr);

    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0, 3);

    fprintf(stdout, "Output on stdout after test %d.\n", n);

    fprintf(stderr, "Output on stderr after test %d.\n", n);

    fflush(stdout);
