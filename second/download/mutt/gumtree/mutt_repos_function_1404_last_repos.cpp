void mutt_set_current_menu_redraw (int redraw)
{
  MUTTMENU *current_menu;

  current_menu = get_current_menu ();
  if (current_menu)
    current_menu->redraw |= redraw;
}