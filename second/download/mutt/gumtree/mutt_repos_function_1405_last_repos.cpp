void mutt_set_current_menu_redraw_full (void)
{
  MUTTMENU *current_menu;

  current_menu = get_current_menu ();
  if (current_menu)
    current_menu->redraw = REDRAW_FULL;
}