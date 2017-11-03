void mutt_curses_error (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  curses_message (1, fmt, ap);
  va_end (ap);
}