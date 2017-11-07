void mutt_block_signals (void)
{
  if (!option (OPTSIGNALSBLOCKED))
  {
    sigemptyset (&Sigset);
    sigaddset (&Sigset, SIGTERM);
    sigaddset (&Sigset, SIGHUP);
    sigaddset (&Sigset, SIGTSTP);
    sigaddset (&Sigset, SIGINT);
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
    sigaddset (&Sigset, SIGWINCH);
#endif
    sigprocmask (SIG_BLOCK, &Sigset, 0);
    set_option (OPTSIGNALSBLOCKED);
  }
}