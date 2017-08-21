  /* Avoid error diagnostic popups since we are crashing on purpose.  */
  disable_debugger(1);
#endif
  (void)argc; (void)argv;
  fprintf(stdout, "Output before crash on stdout from crash test.\n");
  fprintf(stderr, "Output before crash on stderr from crash test.\n");
  fflush(stdout);
