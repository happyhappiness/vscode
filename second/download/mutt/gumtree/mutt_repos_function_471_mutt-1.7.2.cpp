static int vw_printw (SLcurses_Window_Type *win, const char *fmt, va_list ap)
{
  char buf[LONG_STRING];

  (void) SLvsnprintf (buf, sizeof (buf), (char *)fmt, ap);
  SLcurses_waddnstr (win, buf, -1);
  return 0;
}