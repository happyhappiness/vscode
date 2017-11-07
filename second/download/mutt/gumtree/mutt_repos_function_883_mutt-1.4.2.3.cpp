void menu_redraw_status (MUTTMENU *menu)
{
  char buf[STRING];

  snprintf (buf, sizeof (buf), M_MODEFMT, menu->title);
  SETCOLOR (MT_COLOR_STATUS);
  move (option (OPTSTATUSONTOP) ? 0 : LINES - 2, 0);
  mutt_paddstr (COLS, buf);
  SETCOLOR (MT_COLOR_NORMAL);
  menu->redraw &= ~REDRAW_STATUS;
}