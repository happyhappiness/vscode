void mutt_curses_message (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  vsnprintf (Errorbuf, sizeof (Errorbuf), fmt, ap);
  va_end (ap);

  mutt_format_string (Errorbuf, sizeof (Errorbuf),
		      0, COLS-2, 0, 0, Errorbuf, sizeof (Errorbuf), 0);

  if (!option (OPTKEEPQUIET))
  {
    SETCOLOR (MT_COLOR_MESSAGE);
    mvaddstr (LINES - 1, 0, Errorbuf);
    clrtoeol ();
    SETCOLOR (MT_COLOR_NORMAL);
    mutt_refresh ();
  }

  unset_option (OPTMSGERR);
}