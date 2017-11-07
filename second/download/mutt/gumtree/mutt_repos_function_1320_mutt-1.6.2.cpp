static void menu_prev_entry (MUTTMENU *menu)
{
  if (menu->current)
  {
    menu->current--;
    menu->redraw = REDRAW_MOTION;
  }
  else
    mutt_error _("You are on the first entry.");
}