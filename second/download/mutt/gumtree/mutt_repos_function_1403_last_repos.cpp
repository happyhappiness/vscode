void mutt_pop_current_menu (MUTTMENU *menu)
{
  MUTTMENU *prev_menu;

  if (!MenuStackCount ||
      (MenuStack[MenuStackCount - 1] != menu))
  {
    dprint (1, (debugfile, "mutt_pop_current_menu() called with inactive menu\n"));
    return;
  }

  MenuStackCount--;
  prev_menu = get_current_menu ();
  if (prev_menu)
  {
    CurrentMenu = prev_menu->menu;
    prev_menu->redraw = REDRAW_FULL;
  }
  else
  {
    CurrentMenu = MENU_MAIN;
  }
}