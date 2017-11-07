void menu_jump (MUTTMENU *menu)
{
  int n;
  char buf[SHORT_STRING];

  if (menu->max)
  {
    mutt_ungetch (LastKey, 0);
    buf[0] = 0;
    if (mutt_get_field (_("Jump to: "), buf, sizeof (buf), 0) == 0 && buf[0])
    {
      n = atoi (buf) - 1;
      if (n >= 0 && n < menu->max)
      {
	menu->current = n;
	menu->redraw = REDRAW_MOTION;
      }
      else
	mutt_error _("Invalid index number.");
    }
  }
  else
    mutt_error _("No entries.");
}