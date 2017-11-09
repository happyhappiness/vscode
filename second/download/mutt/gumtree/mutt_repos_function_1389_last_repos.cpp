void menu_first_entry (MUTTMENU *menu)
{
  if (menu->max)
  {
    menu->current = 0;
    menu->redraw = REDRAW_MOTION;
  }
  else
    mutt_error _("No entries.");
}