void menu_redraw_motion (MUTTMENU *menu)
{
  char buf[LONG_STRING];
  int old_color, cur_color;

  if (menu->dialog) 
  {
    menu->redraw &= ~REDRAW_MOTION;
    return;
  }

  /* Note: menu->color() for the index can end up retrieving a message
   * over imap (if matching against ~h for instance).  This can
   * generate status messages.  So we want to call it *before* we
   * position the cursor for drawing. */
  old_color = menu->color (menu->oldcurrent);
  mutt_window_move (menu->indexwin, menu->oldcurrent + menu->offset - menu->top, 0);
  ATTRSET(old_color);

  if (option (OPTARROWCURSOR))
  {
    /* clear the pointer */
    addstr ("  ");

    if (menu->redraw & REDRAW_MOTION_RESYNCH)
    {
      menu_make_entry (buf, sizeof (buf), menu, menu->oldcurrent);
      menu_pad_string (menu, buf, sizeof (buf));
      mutt_window_move (menu->indexwin, menu->oldcurrent + menu->offset - menu->top, 3);
      print_enriched_string (old_color, (unsigned char *) buf, 1);
    }

    /* now draw it in the new location */
    SETCOLOR(MT_COLOR_INDICATOR);
    mutt_window_mvaddstr (menu->indexwin, menu->current + menu->offset - menu->top, 0, "->");
  }
  else
  {
    /* erase the current indicator */
    menu_make_entry (buf, sizeof (buf), menu, menu->oldcurrent);
    menu_pad_string (menu, buf, sizeof (buf));
    print_enriched_string (old_color, (unsigned char *) buf, 1);

    /* now draw the new one to reflect the change */
    cur_color = menu->color (menu->current);
    menu_make_entry (buf, sizeof (buf), menu, menu->current);
    menu_pad_string (menu, buf, sizeof (buf));
    SETCOLOR(MT_COLOR_INDICATOR);
    mutt_window_move (menu->indexwin, menu->current + menu->offset - menu->top, 0);
    print_enriched_string (cur_color, (unsigned char *) buf, 0);
  }
  menu->redraw &= REDRAW_STATUS;
  NORMAL_COLOR;
}