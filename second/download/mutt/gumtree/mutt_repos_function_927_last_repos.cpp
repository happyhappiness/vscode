int  mutt_enter_string(char *buf, size_t buflen, int col, int flags)
{
  int rv;
  ENTER_STATE *es = mutt_new_enter_state ();
  do
  {
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
    if (SigWinch)
    {
      SigWinch = 0;
      mutt_resize_screen ();
      clearok(stdscr, TRUE);
    }
#endif
    rv = _mutt_enter_string (buf, buflen, col, flags, 0, NULL, NULL, es);
  }
  while (rv == 1);
  mutt_free_enter_state (&es);
  return rv;
}