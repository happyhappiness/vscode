void mutt_push_current_menu (MUTTMENU *menu)
{
  if (MenuStackCount >= MenuStackLen)
  {
    MenuStackLen += 5;
    safe_realloc (&MenuStack, MenuStackLen * sizeof(MUTTMENU *));
  }

  MenuStack[MenuStackCount++] = menu;
  CurrentMenu = menu->menu;
}