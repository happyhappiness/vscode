  printf ("System: %s %s", uts.sysname, uts.release);
#endif

  printf (" (%s)", uts.machine);

#ifdef NCURSES_VERSION
  printf (" [using ncurses %s]", NCURSES_VERSION);
#elif defined(USE_SLANG_CURSES)
  printf (" [using slang %d]", SLANG_VERSION);
#endif

  puts (_("\nCompile options:"));

#ifdef DOMAIN
  printf ("DOMAIN=\"%s\"\n", DOMAIN);
#else
  puts ("-DOMAIN");
