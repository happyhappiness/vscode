void menu_next_line (MUTTMENU *menu)
{
  if (menu->max)
  {
    if (menu->top + 1 < menu->max)
    {
      menu->top++;
      if (menu->current < menu->top)
	menu->current++;
      menu->redraw = REDRAW_INDEX;
    }
    else
      mutt_error _("You cannot scroll down farther.");
  }
  else
    mutt_error _("No entries.");
}