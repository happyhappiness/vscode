MUTTMENU *mutt_new_menu (void)
{
  MUTTMENU *p = (MUTTMENU *) safe_calloc (1, sizeof (MUTTMENU));

  p->current = 0;
  p->top = 0;
  p->offset = 1;
  p->redraw = REDRAW_FULL;
  p->pagelen = PAGELEN;
  p->color = default_color;
  p->search = menu_search_generic;
  return (p);
}