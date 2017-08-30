#if defined(_WIN32)

  /* Avoid error diagnostic popups since we are crashing on purpose.  */

  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

#endif

  (void)argc; (void)argv;

  fprintf(stdout, "Output before crash on stdout from crash test.\n");

