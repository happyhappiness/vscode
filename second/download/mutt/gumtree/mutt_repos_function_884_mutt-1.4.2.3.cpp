void menu_redraw_index (MUTTMENU *menu)
{
  char buf[STRING];
  int i;

  for (i = menu->top; i < menu->top + menu->pagelen; i++)
  {
    if (i < menu->max)
    {
      menu_make_entry (buf, sizeof (buf), menu, i);
      menu_pad_string (buf, sizeof (buf));

      if (option (OPTARROWCURSOR))
      {
        attrset (menu->color (i));
	CLEARLINE (i - menu->top + menu->offset);

	if (i == menu->current)
	{
	  SETCOLOR (MT_COLOR_INDICATOR);
	  addstr ("->");
          attrset (menu->color (i));
	  addch (' ');
	}
	else
	  move (i - menu->top + menu->offset, 3);

        print_enriched_string (menu->color(i), (unsigned char *) buf, 1);
        SETCOLOR (MT_COLOR_NORMAL);          
      }
      else
      {
	if (i == menu->current)
	{
	  SETCOLOR (MT_COLOR_INDICATOR);
	  BKGDSET (MT_COLOR_INDICATOR);
	}
        else
          attrset (menu->color (i));
            
	CLEARLINE (i - menu->top + menu->offset);
	print_enriched_string (menu->color(i), (unsigned char *) buf, i != menu->current);
        SETCOLOR (MT_COLOR_NORMAL);
        BKGDSET (MT_COLOR_NORMAL);
      }
    }
    else
      CLEARLINE (i - menu->top + menu->offset);
  }
  menu->redraw = 0;
}