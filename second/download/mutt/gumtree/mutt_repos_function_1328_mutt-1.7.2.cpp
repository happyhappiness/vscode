static void menu_length_jump (MUTTMENU *menu, int jumplen)
{
  int tmp, neg = (jumplen >= 0) ? 0 : -1;
  int c = MIN (MenuContext, menu->pagelen / 2);

  if (menu->max)
  {
    /* possible to scroll? */
    if (DIRECTION * menu->top <
	(tmp = (neg ? 0 : (menu->max /*-1*/) - (menu->pagelen /*-1*/))))
    {
      menu->top += jumplen;

      /* jumped too long? */
      if ((neg || !option (OPTMENUMOVEOFF)) &&
	  DIRECTION * menu->top > tmp)
	menu->top = tmp;

      /* need to move the cursor? */
      if ((DIRECTION *
	   (tmp = (menu->current -
		   (menu->top + (neg ? (menu->pagelen - 1) - c : c))
	  ))) < 0)
	menu->current -= tmp;

      menu->redraw = REDRAW_INDEX;
    }
    else if (menu->current != (neg ? 0 : menu->max - 1) && !menu->dialog)
    {
      menu->current += jumplen;
      menu->redraw = REDRAW_MOTION;
    }
    else
      mutt_error (neg ? _("You are on the first page.")
		      : _("You are on the last page."));

    menu->current = MIN (menu->current, menu->max - 1);
    menu->current = MAX (menu->current, 0);
  }
  else
    mutt_error _("No entries.");
}