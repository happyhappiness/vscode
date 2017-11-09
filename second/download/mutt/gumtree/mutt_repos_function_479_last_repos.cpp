void mutt_window_clrtoeol (mutt_window_t *win)
{
  int row, col, curcol;

  if (win->col_offset + win->cols == COLS)
    clrtoeol ();
  else
  {
    getyx (stdscr, row, col);
    curcol = col;
    while (curcol < win->col_offset + win->cols)
    {
      addch (' ');
      curcol++;
    }
    move (row, col);
  }
}