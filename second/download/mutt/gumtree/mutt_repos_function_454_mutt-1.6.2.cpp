static void curses_message (int error, const char *fmt, va_list ap)
{
  char scratch[LONG_STRING];

  vsnprintf (scratch, sizeof (scratch), fmt, ap);

  dprint (1, (debugfile, "%s\n", scratch));
  mutt_format_string (Errorbuf, sizeof (Errorbuf),
		      0, COLS, FMT_LEFT, 0, scratch, sizeof (scratch), 0);

  if (!option (OPTKEEPQUIET))
  {
    if (error)
      BEEP ();
    SETCOLOR (error ? MT_COLOR_ERROR : MT_COLOR_MESSAGE);
    mvaddstr (LINES-1, 0, Errorbuf);
    NORMAL_COLOR;
    clrtoeol ();
    mutt_refresh ();
  }

  if (error)
    set_option (OPTMSGERR);
  else
    unset_option (OPTMSGERR);
}