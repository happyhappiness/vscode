void menu_redraw_full (MUTTMENU *menu)
{
#if ! (defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM))
  mutt_reflow_windows ();
#endif
  NORMAL_COLOR;
  /* clear() doesn't optimize screen redraws */
  move (0, 0);
  clrtobot ();

  if (option (OPTHELP))
  {
    SETCOLOR (MT_COLOR_STATUS);
    mutt_window_move (menu->helpwin, 0, 0);
    mutt_paddstr (menu->helpwin->cols, menu->help);
    NORMAL_COLOR;
  }
  menu->offset = 0;
  menu->pagelen = menu->indexwin->rows;

  mutt_show_error ();

  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
#ifdef USE_SIDEBAR
  menu->redraw |= REDRAW_SIDEBAR;
#endif
}