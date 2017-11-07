void menu_jump (MUTTMENU *menu)
{
  int n;
  char buf[SHORT_STRING];

  if (menu->max)
  {
    mutt_unget_event (LastKey, 0);
    buf[0] = 0;
    if (mutt_get_field (_("Jump to: "), buf, sizeof (buf), 0) == 0 && buf[0])
    {
      if (mutt_atoi (buf, &n) == 0 && n > 0 && n < menu->max + 1)
      {
	n--;	/* msg numbers are 0-based */
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