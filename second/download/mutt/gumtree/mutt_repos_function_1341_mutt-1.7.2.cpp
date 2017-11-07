static void menu_next_entry (MUTTMENU *menu)
{
  if (menu->current < menu->max - 1)
  {
    menu->current++;
    menu->redraw = REDRAW_MOTION;
  }
  else
    mutt_error _("You are on the last entry.");
}