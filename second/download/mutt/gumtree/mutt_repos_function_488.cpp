int mutt_multi_choice (char *prompt, char *letters)
{
  event_t ch;
  int choice;
  char *p;

  SETCOLOR (MT_COLOR_PROMPT);
  mutt_window_mvaddstr (MuttMessageWindow, 0, 0, prompt);
  NORMAL_COLOR;
  mutt_window_clrtoeol (MuttMessageWindow);
  FOREVER
  {
    mutt_refresh ();
    ch  = mutt_getch ();
    /* (ch.ch == 0) is technically possible.  Treat the same as < 0 (abort) */
    if (ch.ch <= 0 || CI_is_return (ch.ch))
    {
      choice = -1;
      break;
    }
    else
    {
      p = strchr (letters, ch.ch);
      if (p)
      {
	choice = p - letters + 1;
	break;
      }
      else if (ch.ch <= '9' && ch.ch > '0')
      {
	choice = ch.ch - '0';
	if (choice <= mutt_strlen (letters))
	  break;
      }
    }
    BEEP ();
  }
  mutt_window_clearline (MuttMessageWindow, 0);
  mutt_refresh ();
  return choice;
}