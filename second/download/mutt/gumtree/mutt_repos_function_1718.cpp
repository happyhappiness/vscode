static void fill_empty_space (int first_row, int num_rows, int width)
{
  /* Fill the remaining rows with blank space */
  SETCOLOR(MT_COLOR_NORMAL);

  int r;
  for (r = 0; r < num_rows; r++)
  {
    mutt_window_move (MuttSidebarWindow, first_row + r, 0);	//RAR rhs
    int i;
    for (i = 0; i < width; i++)
      addch (' ');
  }
}