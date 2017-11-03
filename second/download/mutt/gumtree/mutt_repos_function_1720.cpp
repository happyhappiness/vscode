void mutt_sb_draw (void)
{
  if (!option (OPTSIDEBAR))
    return;

  int num_rows  = MuttSidebarWindow->rows;
  int num_cols  = MuttSidebarWindow->cols;

  int div_width = draw_divider (num_rows, num_cols);
  if (div_width < 0)
    return;

  if (!Incoming)
  {
    fill_empty_space (0, num_rows, SidebarWidth - div_width);
    return;
  }

  if (!prepare_sidebar (num_rows))
    return;

  draw_sidebar (num_rows, num_cols, div_width);
}