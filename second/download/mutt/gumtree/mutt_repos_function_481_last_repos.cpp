void mutt_window_getyx (mutt_window_t *win, int *y, int *x)
{
  int row, col;

  getyx (stdscr, row, col);
  if (y)
    *y = row - win->row_offset;
  if (x)
    *x = col - win->col_offset;
}