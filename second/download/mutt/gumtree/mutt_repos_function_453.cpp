event_t mutt_getch (void)
{
  int ch;
  event_t err = {-1, OP_NULL }, ret;
  event_t timeout = {-2, OP_NULL};

  if (UngetCount)
    return (UngetKeyEvents[--UngetCount]);

  if (!option(OPTIGNOREMACROEVENTS) && MacroBufferCount)
    return (MacroEvents[--MacroBufferCount]);

  SigInt = 0;

  mutt_allow_interrupt (1);
#ifdef KEY_RESIZE
  /* ncurses 4.2 sends this when the screen is resized */
  ch = KEY_RESIZE;
  while (ch == KEY_RESIZE)
#endif /* KEY_RESIZE */
    ch = getch ();
  mutt_allow_interrupt (0);

  if (SigInt)
  {
    mutt_query_exit ();
    return err;
  }

  if(ch == ERR)
  {
    /* either timeout or the terminal has been lost */
    if (!isatty (0))
    {
      endwin ();
      exit (1);
    }
    return timeout;
  }

  if ((ch & 0x80) && option (OPTMETAKEY))
  {
    /* send ALT-x as ESC-x */
    ch &= ~0x80;
    mutt_unget_event (ch, 0);
    ret.ch = '\033';
    ret.op = 0;
    return ret;
  }

  ret.ch = ch;
  ret.op = 0;
  return (ch == ctrl ('G') ? err : ret);
}