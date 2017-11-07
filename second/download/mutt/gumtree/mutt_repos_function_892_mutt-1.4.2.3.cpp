void menu_next_page (MUTTMENU *menu)
{
  if (menu->max)
  {
    if (menu->top + menu->pagelen < menu->max)
    {
      menu->top += menu->pagelen;
      if (menu->current < menu->top)
	menu->current = menu->top;
      menu->redraw = REDRAW_INDEX;
    }
    else if (menu->current != menu->max - 1 && !menu->dialog)
    {
      menu->current = menu->max - 1;
      menu->redraw = REDRAW_MOTION;
    }
    else
      mutt_error _("You are on the last page.");
  }
  else
    mutt_error _("No entries.");
}