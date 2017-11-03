void menu_redraw_index (MUTTMENU *menu)
{
  char buf[LONG_STRING];
  int i;
  int do_color;
  int attr;

  for (i = menu->top; i < menu->top + menu->pagelen; i++)
  {
    if (i < menu->max)
    {
      attr = menu->color(i);

      menu_make_entry (buf, sizeof (buf), menu, i);
      menu_pad_string (menu, buf, sizeof (buf));

      ATTRSET(attr);
      mutt_window_move (menu->indexwin, i - menu->top + menu->offset, 0);
      do_color = 1;

      if (i == menu->current)
      {
	  SETCOLOR(MT_COLOR_INDICATOR);
	  if (option(OPTARROWCURSOR))
	  {
	    addstr ("->");
	    ATTRSET(attr);
	    addch (' ');
	  }
	  else
	    do_color = 0;
      }
      else if (option(OPTARROWCURSOR))
	addstr("   ");

      print_enriched_string (attr, (unsigned char *) buf, do_color);
    }
    else
    {
      NORMAL_COLOR;
      mutt_window_clearline (menu->indexwin, i - menu->top + menu->offset);
    }
  }
  NORMAL_COLOR;
  menu->redraw = 0;
}