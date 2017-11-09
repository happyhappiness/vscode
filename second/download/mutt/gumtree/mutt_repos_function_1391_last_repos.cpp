void menu_current_top (MUTTMENU *menu)
{
  if (menu->max)
  {
    menu->top = menu->current;
    menu->redraw = REDRAW_INDEX;
  }
  else
    mutt_error _("No entries.");
}