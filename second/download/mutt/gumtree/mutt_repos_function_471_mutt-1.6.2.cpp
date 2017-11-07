int mutt_multi_choice (char *prompt, char *letters)
{
  event_t ch;
  int choice;
  char *p;

  SETCOLOR (MT_COLOR_PROMPT);
  mvaddstr (LINES - 1, 0, prompt);
  NORMAL_COLOR;
  clrtoeol ();
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
  CLEARLINE (LINES - 1);
  mutt_refresh ();
  return choice;
}