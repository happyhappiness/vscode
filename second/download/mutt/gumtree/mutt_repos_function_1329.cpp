void menu_next_page (MUTTMENU *menu)
{
  menu_length_jump (menu, MAX (menu->pagelen /* - MenuOverlap */, 0));
}