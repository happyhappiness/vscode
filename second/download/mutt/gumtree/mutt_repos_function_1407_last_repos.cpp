void mutt_set_menu_redraw_full (int menu_type)
{
  if (CurrentMenu == menu_type)
    mutt_set_current_menu_redraw_full ();
}