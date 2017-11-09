static void exit_handler (int sig)
{
  curs_set (1);
  endwin (); /* just to be safe */
#if SYS_SIGLIST_DECLARED
  printf(_("%s...  Exiting.\n"), sys_siglist[sig]);
#else
#if (__sun__ && __svr4__)
  printf(_("Caught %s...  Exiting.\n"), _sys_siglist[sig]);
#else
#if (__alpha && __osf__)
  printf(_("Caught %s...  Exiting.\n"), __sys_siglist[sig]);
#else
  printf(_("Caught signal %d...  Exiting.\n"), sig);
#endif
#endif
#endif
  exit (0);
}