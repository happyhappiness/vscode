int _mutt_enter_fname (const char *prompt, char *buf, size_t blen, int *redraw, int buffy, int multiple, char ***files, int *numfiles)
{
  event_t ch;

  SETCOLOR (MT_COLOR_PROMPT);
  mutt_window_mvaddstr (MuttMessageWindow, 0, 0, (char *) prompt);
  addstr (_(" ('?' for list): "));
  NORMAL_COLOR;
  if (buf[0])
    addstr (buf);
  mutt_window_clrtoeol (MuttMessageWindow);
  mutt_refresh ();

  ch = mutt_getch();
  if (ch.ch < 0)
  {
    mutt_window_clearline (MuttMessageWindow, 0);
    return (-1);
  }
  else if (ch.ch == '?')
  {
    mutt_refresh ();
    buf[0] = 0;
    _mutt_select_file (buf, blen, MUTT_SEL_FOLDER | (multiple ? MUTT_SEL_MULTI : 0), 
		       files, numfiles);
    *redraw = REDRAW_FULL;
  }
  else
  {
    char *pc = safe_malloc (mutt_strlen (prompt) + 3);

    sprintf (pc, "%s: ", prompt);	/* __SPRINTF_CHECKED__ */
    mutt_unget_event (ch.op ? 0 : ch.ch, ch.op ? ch.op : 0);
    if (_mutt_get_field (pc, buf, blen, (buffy ? MUTT_EFILE : MUTT_FILE) | MUTT_CLEAR, multiple, files, numfiles)
	!= 0)
      buf[0] = 0;
    MAYBE_REDRAW (*redraw);
    FREE (&pc);
  }

  return 0;
}