void menu_prev_line (MUTTMENU *menu)
{
  if (menu->top > 0)
  {
    int c = MIN (MenuContext, menu->pagelen / 2);

    menu->top--;
    if (menu->current >= menu->top + menu->pagelen - c && menu->current > 1)
      menu->current--;
    menu->redraw = REDRAW_INDEX;
  }
  else
    mutt_error _("You cannot scroll up farther.");
}