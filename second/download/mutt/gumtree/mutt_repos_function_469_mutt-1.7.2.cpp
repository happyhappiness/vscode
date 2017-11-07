int mutt_window_mvaddch (mutt_window_t *win, int row, int col, const chtype ch)
{
  return mvaddch (win->row_offset + row, win->col_offset + col, ch);
}