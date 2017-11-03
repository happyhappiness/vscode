void menu_top_page (MUTTMENU *menu)
{
  if (menu->current != menu->top)
  {
    menu->current = menu->top;
    menu->redraw = REDRAW_MOTION;
  }
}