static void sighandler (int sig)
{
  int save_errno = errno;

  switch (sig)
  {
    case SIGTSTP: /* user requested a suspend */
      if (!option (OPTSUSPEND))
        break;
      IsEndwin = isendwin ();
      curs_set (1);
      if (!IsEndwin)
	endwin ();
      kill (0, SIGSTOP);

    case SIGCONT:
      if (!IsEndwin)
	refresh ();
      mutt_curs_set (-1);
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
      /* We don't receive SIGWINCH when suspended; however, no harm is done by
       * just assuming we received one, and triggering the 'resize' anyway. */
      SigWinch = 1;
#endif
      break;

#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
    case SIGWINCH:
      SigWinch = 1;
      break;
#endif

    case SIGINT:
      SigInt = 1;
      break;

  }
  errno = save_errno;
}