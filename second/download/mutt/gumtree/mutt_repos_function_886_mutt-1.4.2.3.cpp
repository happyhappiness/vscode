void menu_redraw_current (MUTTMENU *menu)
{
  char buf[STRING];
  
  move (menu->current + menu->offset - menu->top, 0);
  menu_make_entry (buf, sizeof (buf), menu, menu->current);
  menu_pad_string (buf, sizeof (buf));

  if (option (OPTARROWCURSOR))
  {
    int attr = menu->color (menu->current);
    attrset (attr);
    clrtoeol ();
    SETCOLOR (MT_COLOR_INDICATOR);
    addstr ("->");
    attrset (attr);
    addch (' ');
    menu_pad_string (buf, sizeof (buf));
    print_enriched_string (menu->color(menu->current), (unsigned char *) buf, 1);
    SETCOLOR (MT_COLOR_NORMAL);
  }
  else
  {
    SETCOLOR (MT_COLOR_INDICATOR);
    BKGDSET (MT_COLOR_INDICATOR);
    clrtoeol ();
    print_enriched_string (menu->color(menu->current), (unsigned char *) buf, 0);
    SETCOLOR (MT_COLOR_NORMAL);
    BKGDSET (MT_COLOR_NORMAL);
  }
  menu->redraw &= REDRAW_STATUS;
}