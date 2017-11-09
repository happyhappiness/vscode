int _mutt_get_field (const char *field, char *buf, size_t buflen, int complete, int multiple, char ***files, int *numfiles)
{
  int ret;
  int x;

  ENTER_STATE *es = mutt_new_enter_state();
  
  do
  {
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
    if (SigWinch)
    {
      SigWinch = 0;
      mutt_resize_screen ();
      clearok(stdscr, TRUE);
      mutt_current_menu_redraw ();
    }
#endif
    mutt_window_clearline (MuttMessageWindow, 0);
    SETCOLOR (MT_COLOR_PROMPT);
    addstr ((char *)field); /* cast to get around bad prototypes */
    NORMAL_COLOR;
    mutt_refresh ();
    mutt_window_getyx (MuttMessageWindow, NULL, &x);
    ret = _mutt_enter_string (buf, buflen, x, complete, multiple, files, numfiles, es);
  }
  while (ret == 1);
  mutt_window_clearline (MuttMessageWindow, 0);
  mutt_free_enter_state (&es);

  return (ret);
}