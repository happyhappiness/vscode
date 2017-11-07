void menu_check_recenter (MUTTMENU *menu)
{
  if (menu->max <= menu->pagelen && menu->top != 0)
  {
    menu->top = 0;
    set_option (OPTNEEDREDRAW);
    menu->redraw |= REDRAW_INDEX;
  }
  else if (menu->current >= menu->top + menu->pagelen)
  {
    if (option (OPTMENUSCROLL) || (menu->pagelen <= 0))
      menu->top = menu->current - menu->pagelen + 1;
    else
      menu->top += menu->pagelen * ((menu->current - menu->top) / menu->pagelen);
    menu->redraw |= REDRAW_INDEX;
  }
  else if (menu->current < menu->top)
  {
    if (option (OPTMENUSCROLL) || (menu->pagelen <= 0))
      menu->top = menu->current;
    else
    {
      menu->top -= menu->pagelen * ((menu->top + menu->pagelen - 1 - menu->current) / menu->pagelen);
      if (menu->top < 0)
	menu->top = 0;
    }
    menu->redraw |= REDRAW_INDEX;
  }
}