void mutt_query_exit (void)
{
  mutt_flushinp ();
  curs_set (1);
  if (Timeout)
    timeout (-1); /* restore blocking operation */
  if (mutt_yesorno (_("Exit Mutt?"), 1) == 1)
  {
    endwin ();
    exit (1);
  }
  mutt_clear_error();
  mutt_curs_set (-1);
  SigInt = 0;
}