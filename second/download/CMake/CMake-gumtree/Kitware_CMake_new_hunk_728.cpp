  fflush(stdout);

  fflush(stderr);

  /* Sleep for 1 second.  */

  testProcess_sleep(1);

  fprintf(stdout, "Output on stdout after sleep.\n");

  fprintf(stderr, "Output on stderr after sleep.\n");

  fflush(stdout);

