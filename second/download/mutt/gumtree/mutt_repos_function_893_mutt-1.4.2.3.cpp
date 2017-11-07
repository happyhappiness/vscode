void menu_prev_page (MUTTMENU *menu)
{
  if (menu->top > 0)
  {
    if ((menu->top -= menu->pagelen) < 0)
      menu->top = 0;
    if (menu->current >= menu->top + menu->pagelen)
      menu->current = menu->top + menu->pagelen - 1;
    menu->redraw = REDRAW_INDEX;
  }
  else if (menu->current && !menu->dialog)
  {
    menu->current = 0;
    menu->redraw = REDRAW_MOTION;
  }
  else
    mutt_error _("You are on the first page.");
}