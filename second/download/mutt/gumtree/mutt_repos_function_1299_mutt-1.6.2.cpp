void menu_redraw_motion (MUTTMENU *menu)
{
  char buf[LONG_STRING];

  if (menu->dialog) 
  {
    menu->redraw &= ~REDRAW_MOTION;
    return;
  }
  
  move (menu->oldcurrent + menu->offset - menu->top, 0);
  ATTRSET(menu->color (menu->oldcurrent));

  if (option (OPTARROWCURSOR))
  {
    /* clear the pointer */
    addstr ("  ");

    if (menu->redraw & REDRAW_MOTION_RESYNCH)
    {
      menu_make_entry (buf, sizeof (buf), menu, menu->oldcurrent);
      menu_pad_string (buf, sizeof (buf));
      move (menu->oldcurrent + menu->offset - menu->top, 3);
      print_enriched_string (menu->color(menu->oldcurrent), (unsigned char *) buf, 1);
    }

    /* now draw it in the new location */
    SETCOLOR(MT_COLOR_INDICATOR);
    mvaddstr(menu->current + menu->offset - menu->top, 0, "->");
  }
  else
  {
    /* erase the current indicator */
    menu_make_entry (buf, sizeof (buf), menu, menu->oldcurrent);
    menu_pad_string (buf, sizeof (buf));
    print_enriched_string (menu->color(menu->oldcurrent), (unsigned char *) buf, 1);

    /* now draw the new one to reflect the change */
    menu_make_entry (buf, sizeof (buf), menu, menu->current);
    menu_pad_string (buf, sizeof (buf));
    SETCOLOR(MT_COLOR_INDICATOR);
    move(menu->current - menu->top + menu->offset, 0);
    print_enriched_string (menu->color(menu->current), (unsigned char *) buf, 0);
  }
  menu->redraw &= REDRAW_STATUS;
  NORMAL_COLOR;
}