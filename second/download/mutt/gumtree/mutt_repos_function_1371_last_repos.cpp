void menu_redraw_status (MUTTMENU *menu)
{
  char buf[STRING];

  snprintf (buf, sizeof (buf), MUTT_MODEFMT, menu->title);
  SETCOLOR (MT_COLOR_STATUS);
  mutt_window_move (menu->statuswin, 0, 0);
  mutt_paddstr (menu->statuswin->cols, buf);
  NORMAL_COLOR;
  menu->redraw &= ~REDRAW_STATUS;
}