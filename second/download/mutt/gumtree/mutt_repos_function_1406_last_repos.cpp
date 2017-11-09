void mutt_set_menu_redraw (int menu_type, int redraw)
{
  if (CurrentMenu == menu_type)
    mutt_set_current_menu_redraw (redraw);
}