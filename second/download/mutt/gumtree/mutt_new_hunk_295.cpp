
int mutt_window_mvprintw (mutt_window_t *win, int row, int col, const char *fmt, ...)
{
  va_list ap;
  int rv;

  if ((rv = mutt_window_move (win, row, col)) != ERR)
  {
    va_start (ap, fmt);
    rv = vw_printw (stdscr, fmt, ap);
    va_end (ap);
  }

