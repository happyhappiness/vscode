  fflush(stdout);
  fflush(stderr);
#if defined(_WIN32)
  Sleep(5000);
#else
  sleep(5);
#endif
  fprintf(stdout, "Output after sleep on stdout from timeout test.\n");
  fprintf(stderr, "Output after sleep on stderr from timeout test.\n");
