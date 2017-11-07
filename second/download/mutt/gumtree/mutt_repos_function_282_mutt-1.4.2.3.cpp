event_t mutt_getch (void)
{
  int ch;
  event_t err = {-1, OP_NULL }, ret;

  if (UngetCount)
    return (KeyEvent[--UngetCount]);

  SigInt = 0;

#ifdef KEY_RESIZE
  /* ncurses 4.2 sends this when the screen is resized */
  ch = KEY_RESIZE;
  while (ch == KEY_RESIZE)
#endif /* KEY_RESIZE */
    ch = getch ();

  if (SigInt)
    mutt_query_exit ();

  if(ch == ERR)
    return err;
  
  if ((ch & 0x80) && option (OPTMETAKEY))
  {
    /* send ALT-x as ESC-x */
    ch &= ~0x80;
    mutt_ungetch (ch, 0);
    ret.ch = '\033';
    ret.op = 0;
    return ret;
  }

  ret.ch = ch;
  ret.op = 0;
  return (ch == ctrl ('G') ? err : ret);
}