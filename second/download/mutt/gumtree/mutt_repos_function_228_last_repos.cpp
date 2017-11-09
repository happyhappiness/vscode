void mutt_shell_escape (void)
{
  char buf[LONG_STRING];

  buf[0] = 0;
  if (mutt_get_field (_("Shell command: "), buf, sizeof (buf), MUTT_CMD) == 0)
  {
    if (!buf[0] && Shell)
      strfcpy (buf, Shell, sizeof (buf));
    if(buf[0])
    {
      mutt_window_clearline (MuttMessageWindow, 0);
      mutt_endwin (NULL);
      fflush (stdout);
      if (mutt_system (buf) != 0 || option (OPTWAITKEY))
	mutt_any_key_to_continue (NULL);
    }
  }
}