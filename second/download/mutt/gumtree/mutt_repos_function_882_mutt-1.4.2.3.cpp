void menu_redraw_full (MUTTMENU *menu)
{
  SETCOLOR (MT_COLOR_NORMAL);
  /* clear() doesn't optimize screen redraws */
  move (0, 0);
  clrtobot ();

  if (option (OPTHELP))
  {
    SETCOLOR (MT_COLOR_STATUS);
    move (option (OPTSTATUSONTOP) ? LINES-2 : 0, 0);
    mutt_paddstr (COLS, menu->help);
    SETCOLOR (MT_COLOR_NORMAL);
    menu->offset = 1;
    menu->pagelen = LINES - 3;
  }
  else
  {
    menu->offset = option (OPTSTATUSONTOP) ? 1 : 0;
    menu->pagelen = LINES - 2;
  }

  mutt_show_error ();

  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
}