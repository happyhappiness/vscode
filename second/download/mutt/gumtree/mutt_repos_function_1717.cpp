static int draw_divider (int num_rows, int num_cols)
{
  /* Calculate the width of the delimiter in screen cells */
  int delim_len = mutt_strwidth (SidebarDividerChar);

  if (delim_len < 1)
    return delim_len;

  if (delim_len > num_cols)
    return 0;

  SETCOLOR(MT_COLOR_DIVIDER);

  int i;
  for (i = 0; i < num_rows; i++)
  {
    mutt_window_move (MuttSidebarWindow, i, SidebarWidth - delim_len);	//RAR 0 for rhs
    addstr (NONULL(SidebarDividerChar));
  }

  return delim_len;
}