void menu_next_line (MUTTMENU *menu)
{
  if (menu->max)
  {
    int c = MIN (MenuContext, menu->pagelen / 2);

    if (menu->top + 1 < menu->max - c
      && (option(OPTMENUMOVEOFF) || (menu->max > menu->pagelen && menu->top < menu->max - menu->pagelen)))
    {
      menu->top++;
      if (menu->current < menu->top + c && menu->current < menu->max - 1)
	menu->current++;
      menu->redraw = REDRAW_INDEX;
    }
    else
      mutt_error _("You cannot scroll down farther.");
  }
  else
    mutt_error _("No entries.");
}