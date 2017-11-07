void menu_current_bottom (MUTTMENU *menu)
{
  if (menu->max)
  {
    menu->top = menu->current - menu->pagelen + 1;
    if (menu->top < 0)
      menu->top = 0;
    menu->redraw = REDRAW_INDEX;
  }
  else
    mutt_error _("No entries.");
}