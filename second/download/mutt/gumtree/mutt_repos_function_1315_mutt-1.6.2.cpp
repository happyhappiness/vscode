void menu_last_entry (MUTTMENU *menu)
{
  if (menu->max)
  {
    menu->current = menu->max - 1;
    menu->redraw = REDRAW_MOTION;
  }
  else
    mutt_error _("No entries.");
}