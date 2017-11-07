void menu_prev_line (MUTTMENU *menu)
{
  if (menu->top > 0)
  {
    menu->top--;
    if (menu->current >= menu->top + menu->pagelen)
      menu->current--;
    menu->redraw = REDRAW_INDEX;
  }
  else
    mutt_error _("You cannot scroll up farther.");
}