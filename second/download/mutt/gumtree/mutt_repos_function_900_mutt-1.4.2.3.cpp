void menu_half_down (MUTTMENU *menu)
{
  if (menu->max)
  {
    if (menu->top + menu->pagelen < menu->max)
    {
      menu->top += menu->pagelen / 2;
      if (menu->current < menu->top)
	menu->current = menu->top;
      menu->redraw = REDRAW_INDEX;
    }
    else if (menu->current != menu->max - 1 && !menu->dialog)
    {
      menu->current = menu->max - 1;
      menu->redraw = REDRAW_INDEX;
    }
    else
      mutt_error _("Last entry is shown.");
  }
  else
    mutt_error _("No entries.");
}