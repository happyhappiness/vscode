void menu_prev_page (MUTTMENU *menu)
{
  menu_length_jump (menu, 0 - MAX (menu->pagelen /* - MenuOverlap */, 0));
}