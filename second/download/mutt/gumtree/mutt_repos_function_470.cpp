int mutt_window_mvaddstr (mutt_window_t *win, int row, int col, const char *str)
{
  return mvaddstr (win->row_offset + row, win->col_offset + col, str);
}