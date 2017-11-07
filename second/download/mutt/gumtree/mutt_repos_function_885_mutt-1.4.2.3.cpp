void menu_redraw_motion (MUTTMENU *menu)
{
  char buf[STRING];

  if (menu->dialog) 
  {
    menu->redraw &= ~REDRAW_MOTION;
    return;
  }
  
  move (menu->oldcurrent + menu->offset - menu->top, 0);
  SETCOLOR (MT_COLOR_NORMAL);
  BKGDSET (MT_COLOR_NORMAL);

  if (option (OPTARROWCURSOR))
  {
    /* clear the pointer */
    attrset (menu->color (menu->oldcurrent));
    addstr ("  ");

    if (menu->redraw & REDRAW_MOTION_RESYNCH)
    {
      clrtoeol ();
      menu_make_entry (buf, sizeof (buf), menu, menu->oldcurrent);
      menu_pad_string (buf, sizeof (buf));
      move (menu->oldcurrent + menu->offset - menu->top, 3);
      print_enriched_string (menu->color(menu->oldcurrent), (unsigned char *) buf, 1);
      SETCOLOR (MT_COLOR_NORMAL);
    }

    /* now draw it in the new location */
    move (menu->current + menu->offset - menu->top, 0);
    SETCOLOR (MT_COLOR_INDICATOR);
    addstr ("->");
    SETCOLOR (MT_COLOR_NORMAL);
  }
  else
  {
    /* erase the current indicator */
    attrset (menu->color (menu->oldcurrent));
    clrtoeol ();
    menu_make_entry (buf, sizeof (buf), menu, menu->oldcurrent);
    menu_pad_string (buf, sizeof (buf));
    print_enriched_string (menu->color(menu->oldcurrent), (unsigned char *) buf, 1);

    /* now draw the new one to reflect the change */
    menu_make_entry (buf, sizeof (buf), menu, menu->current);
    menu_pad_string (buf, sizeof (buf));
    SETCOLOR (MT_COLOR_INDICATOR);
    BKGDSET (MT_COLOR_INDICATOR);
    CLEARLINE (menu->current - menu->top + menu->offset);
    print_enriched_string (menu->color(menu->current), (unsigned char *) buf, 0);
    SETCOLOR (MT_COLOR_NORMAL);
    BKGDSET (MT_COLOR_NORMAL);
  }
  menu->redraw &= REDRAW_STATUS;
}