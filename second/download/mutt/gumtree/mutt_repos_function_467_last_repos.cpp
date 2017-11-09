void mutt_curses_message (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  curses_message (0, fmt, ap);
  va_end (ap);
}