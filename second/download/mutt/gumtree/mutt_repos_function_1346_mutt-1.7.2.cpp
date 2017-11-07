MUTTMENU *mutt_new_menu (int menu)
{
  MUTTMENU *p = (MUTTMENU *) safe_calloc (1, sizeof (MUTTMENU));

  if ((menu < 0) || (menu >= MENU_MAX))
    menu = MENU_GENERIC;

  p->menu = menu;
  p->current = 0;
  p->top = 0;
  p->offset = 0;
  p->redraw = REDRAW_FULL;
  p->pagelen = MuttIndexWindow->rows;
  p->indexwin = MuttIndexWindow;
  p->statuswin = MuttStatusWindow;
  p->helpwin = MuttHelpWindow;
  p->messagewin = MuttMessageWindow;
  p->color = default_color;
  p->search = menu_search_generic;
  return (p);
}