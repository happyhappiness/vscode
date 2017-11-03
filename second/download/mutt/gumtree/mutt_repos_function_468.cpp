int mutt_window_move (mutt_window_t *win, int row, int col)
{
  return move (win->row_offset + row, win->col_offset + col);
}