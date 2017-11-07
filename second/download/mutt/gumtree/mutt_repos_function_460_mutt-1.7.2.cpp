static void curses_message (int error, const char *fmt, va_list ap)
{
  char scratch[LONG_STRING];

  vsnprintf (scratch, sizeof (scratch), fmt, ap);

  dprint (1, (debugfile, "%s\n", scratch));
  mutt_format_string (Errorbuf, sizeof (Errorbuf),
		      0, MuttMessageWindow->cols, FMT_LEFT, 0, scratch, sizeof (scratch), 0);

  if (!option (OPTKEEPQUIET))
  {
    if (error)
      BEEP ();
    SETCOLOR (error ? MT_COLOR_ERROR : MT_COLOR_MESSAGE);
    mutt_window_mvaddstr (MuttMessageWindow, 0, 0, Errorbuf);
    NORMAL_COLOR;
    mutt_window_clrtoeol (MuttMessageWindow);
    mutt_refresh ();
  }

  if (error)
    set_option (OPTMSGERR);
  else
    unset_option (OPTMSGERR);
}