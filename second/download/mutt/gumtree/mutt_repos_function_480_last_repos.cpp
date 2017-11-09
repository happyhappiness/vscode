void mutt_window_clearline (mutt_window_t *win, int row)
{
  mutt_window_move (win, row, 0);
  mutt_window_clrtoeol (win);
}