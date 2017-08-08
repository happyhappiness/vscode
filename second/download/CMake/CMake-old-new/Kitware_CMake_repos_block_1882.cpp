{
  /* Prepare a pointer to an invalid address.  Don't use null, because
  dereferencing null is undefined behaviour and compilers are free to
  do whatever they want. ex: Clang will warn at compile time, or even
  optimize away the write. We hope to 'outsmart' them by using
  'volatile' and a slightly larger address, based on a runtime value. */
  volatile int* invalidAddress = 0;
  invalidAddress += argc ? 1 : 2;

#if defined(_WIN32)
  /* Avoid error diagnostic popups since we are crashing on purpose.  */
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#elif defined(__BEOS__) || defined(__HAIKU__)
  /* Avoid error diagnostic popups since we are crashing on purpose.  */
  disable_debugger(1);
#endif
  (void)argc;
  (void)argv;
  fprintf(stdout, "Output before crash on stdout from crash test.\n");
  fprintf(stderr, "Output before crash on stderr from crash test.\n");
  fflush(stdout);
  fflush(stderr);
  assert(invalidAddress); /* Quiet Clang scan-build. */
  /* Provoke deliberate crash by writing to the invalid address. */
  *invalidAddress = 0;
  fprintf(stdout, "Output after crash on stdout from crash test.\n");
  fprintf(stderr, "Output after crash on stderr from crash test.\n");
  return 0;
}