static MUTTMENU *get_current_menu (void)
{
  return MenuStackCount ? MenuStack[MenuStackCount - 1] : NULL;
}