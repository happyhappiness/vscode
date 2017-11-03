void menu_redraw_current (MUTTMENU *menu)
{
  char buf[LONG_STRING];
  int attr = menu->color (menu->current);

  mutt_window_move (menu->indexwin, menu->current + menu->offset - menu->top, 0);
  menu_make_entry (buf, sizeof (buf), menu, menu->current);
  menu_pad_string (menu, buf, sizeof (buf));

  SETCOLOR(MT_COLOR_INDICATOR);
  if (option (OPTARROWCURSOR))
  {
    addstr ("->");
    ATTRSET(attr);
    addch (' ');
    menu_pad_string (menu, buf, sizeof (buf));
    print_enriched_string (attr, (unsigned char *) buf, 1);
  }
  else
    print_enriched_string (attr, (unsigned char *) buf, 0);
  menu->redraw &= REDRAW_STATUS;
  NORMAL_COLOR;
}