void mutt_signal_init (void)
{
  struct sigaction act;

  sigemptyset (&act.sa_mask);
  act.sa_flags = 0;
  act.sa_handler = SIG_IGN;
  sigaction (SIGPIPE, &act, NULL);

  act.sa_handler = exit_handler;
  sigaction (SIGTERM, &act, NULL);
  sigaction (SIGHUP, &act, NULL);
  sigaction (SIGQUIT, &act, NULL);

  /* we want to avoid race conditions */
  sigaddset (&act.sa_mask, SIGTSTP);

  act.sa_handler = sighandler;

  /* we want SIGALRM to abort the current syscall, so we do this before
   * setting the SA_RESTART flag below.  currently this is only used to
   * timeout on a connect() call in a reasonable amount of time.
   */
  sigaction (SIGALRM, &act, NULL);

  /* we also don't want to mess with interrupted system calls */
#ifdef SA_RESTART
  act.sa_flags = SA_RESTART;
#endif

  sigaction (SIGCONT, &act, NULL);
  sigaction (SIGTSTP, &act, NULL);
  sigaction (SIGINT, &act, NULL);
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
  sigaction (SIGWINCH, &act, NULL);
#endif

  /* POSIX doesn't allow us to ignore SIGCHLD,
   * so we just install a dummy handler for it
   */
  act.sa_handler = chld_handler;
  /* don't need to block any other signals here */
  sigemptyset (&act.sa_mask);
  /* we don't want to mess with stopped children */
  act.sa_flags |= SA_NOCLDSTOP;
  sigaction (SIGCHLD, &act, NULL);

#ifdef USE_SLANG_CURSES
  /* This bit of code is required because of the implementation of
   * SLcurses_wgetch().  If a signal is received (like SIGWINCH) when we
   * are in blocking mode, SLsys_getkey() will not return an error unless
   * a handler function is defined and it returns -1.  This is needed so
   * that if the user resizes the screen while at a prompt, it will just
   * abort and go back to the main-menu.
   */
  SLang_getkey_intr_hook = mutt_intr_hook;
#endif
}