int _mutt_get_field (const char *field, char *buf, size_t buflen, int complete, int multiple, char ***files, int *numfiles)
{
  int ret;
  int x, y;

  ENTER_STATE *es = mutt_new_enter_state();
  
  do
  {
    CLEARLINE (LINES-1);
    SETCOLOR (MT_COLOR_PROMPT);
    addstr ((char *)field); /* cast to get around bad prototypes */
    NORMAL_COLOR;
    mutt_refresh ();
    getyx (stdscr, y, x);
    ret = _mutt_enter_string (buf, buflen, y, x, complete, multiple, files, numfiles, es);
  }
  while (ret == 1);
  CLEARLINE (LINES-1);
  mutt_free_enter_state (&es);
  
  return (ret);
}