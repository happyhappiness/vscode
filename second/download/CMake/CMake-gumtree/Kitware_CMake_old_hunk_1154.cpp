    fprintf(stderr, "Output on stderr after test %d.\n", n);

    fflush(stdout);

    fflush(stderr);

#if _WIN32

    if(argv0) { free(argv0); }

#endif

    return r;
