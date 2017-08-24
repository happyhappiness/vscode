{
  /* Force color according to http://bixense.com/clicolors/ convention.  */
  {
    const char* clicolor_force = getenv("CLICOLOR_FORCE");
    if (clicolor_force && *clicolor_force &&
        strcmp(clicolor_force, "0") != 0) {
      return 1;
    }
  }

  /* If running inside emacs the terminal is not VT100.  Some emacs
     seem to claim the TERM is xterm even though they do not support
     VT100 escapes.  */
  {
    const char* emacs = getenv("EMACS");
    if (emacs && *emacs == 't') {
      return 0;
    }
  }

  /* Check for a valid terminal.  */
  if (!default_vt100) {
    const char** t = 0;
    const char* term = getenv("TERM");
    if (term) {
      for (t = kwsysTerminalVT100Names; *t && strcmp(term, *t) != 0; ++t) {
      }
    }
    if (!(t && *t)) {
      return 0;
    }
  }

#if defined(KWSYS_TERMINAL_ISATTY_WORKS)
  /* Make sure the stream is a tty. */
  (void)default_tty;
  return isatty(fileno(stream)) ? 1 : 0;
#else
  /* Check for cases in which the stream is definitely not a tty.  */
  if (kwsysTerminalStreamIsNotInteractive(stream)) {
    return 0;
  }

  /* Use the provided default for whether this is a tty.  */
  return default_tty;
#endif
}