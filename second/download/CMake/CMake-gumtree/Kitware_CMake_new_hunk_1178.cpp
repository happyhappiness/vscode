  vfprintf(stderr, msg, ap);

  va_end(ap);

  fprintf(stderr, "\n");

  // On Windows, some tools may inject extra threads.

  // exit() may block on locks held by those threads, so forcibly exit.

  fflush(stderr);

  fflush(stdout);

  ExitProcess(1);

}



static void usage(const char* msg) {

  Fatal("%s\n\nusage:\n    "

          "cmcldeps "

