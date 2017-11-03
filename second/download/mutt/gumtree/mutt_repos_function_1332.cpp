void menu_half_up (MUTTMENU *menu)
{
  menu_length_jump (menu, 0 - menu->pagelen / 2);
}