void menu_check_recenter (MUTTMENU *menu)
{
  int c = MIN (MenuContext, menu->pagelen / 2);
  int old_top = menu->top;

  if (!option (OPTMENUMOVEOFF) && menu->max <= menu->pagelen) /* less entries than lines */
  {
    if (menu->top != 0) 
    {
      menu->top = 0;
      set_option (OPTNEEDREDRAW);
    }
  }
  else 
  {
    if (option (OPTMENUSCROLL) || (menu->pagelen <= 0) || (c < MenuContext))
    {
      if (menu->current < menu->top + c)
	menu->top = menu->current - c;
      else if (menu->current >= menu->top + menu->pagelen - c)
	menu->top = menu->current - menu->pagelen + c + 1;
    }
    else
    {
      if (menu->current < menu->top + c)
	menu->top -= (menu->pagelen - c) * ((menu->top + menu->pagelen - 1 - menu->current) / (menu->pagelen - c)) - c;
      else if ((menu->current >= menu->top + menu->pagelen - c))
	menu->top += (menu->pagelen - c) * ((menu->current - menu->top) / (menu->pagelen - c)) - c;	
    }
  }

  if (!option (OPTMENUMOVEOFF)) /* make entries stick to bottom */
    menu->top = MIN (menu->top, menu->max - menu->pagelen);
  menu->top = MAX (menu->top, 0);

  if (menu->top != old_top)
    menu->redraw |= REDRAW_INDEX;
}