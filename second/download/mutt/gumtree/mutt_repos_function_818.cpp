int mutt_alloc_color (int fg, int bg)
{
  COLOR_LIST *p = ColorList;
  int i;
  
#if defined (USE_SLANG_CURSES)
  char fgc[SHORT_STRING], bgc[SHORT_STRING];
#endif

  /* check to see if this color is already allocated to save space */
  while (p)
  {
    if (p->fg == fg && p->bg == bg)
    {
      (p->count)++;
      return (COLOR_PAIR (p->index));
    }
    p = p->next;
  }

  /* check to see if there are colors left */
  if (++UserColors > COLOR_PAIRS) return (A_NORMAL);

  /* find the smallest available index (object) */
  i = 1;
  FOREVER
  {
    p = ColorList;
    while (p)
    {
      if (p->index == i) break;
      p = p->next;
    }
    if (p == NULL) break;
    i++;
  }

  p = (COLOR_LIST *) safe_malloc (sizeof (COLOR_LIST));
  p->next = ColorList;
  ColorList = p;

  p->index = i;
  p->count = 1;
  p->bg = bg;
  p->fg = fg;

#if defined (USE_SLANG_CURSES)
  if (fg == COLOR_DEFAULT || bg == COLOR_DEFAULT)
    SLtt_set_color (i, NULL, get_color_name (fgc, sizeof (fgc), fg), get_color_name (bgc, sizeof (bgc), bg));
  else
#elif defined (HAVE_USE_DEFAULT_COLORS)
  if (fg == COLOR_DEFAULT)
    fg = -1;
  if (bg == COLOR_DEFAULT)
    bg = -1;
#endif

  init_pair(i, fg, bg);

  dprint (3, (debugfile,"mutt_alloc_color(): Color pairs used so far: %d\n",
	      UserColors));

  return (COLOR_PAIR (p->index));
}