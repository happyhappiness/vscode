int mutt_multi_choice (char *prompt, char *letters)
{
  event_t ch;
  int choice;
  int redraw = 1, prompt_lines = 1;
  char *p;

  FOREVER
  {
    if (redraw || SigWinch)
    {
      redraw = 0;
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
      if (SigWinch)
      {
        SigWinch = 0;
        mutt_resize_screen ();
        clearok (stdscr, TRUE);
        mutt_current_menu_redraw ();
      }
#endif
      if (MuttMessageWindow->cols)
      {
        prompt_lines = (mutt_strwidth (prompt) + MuttMessageWindow->cols - 1) /
          MuttMessageWindow->cols;
        prompt_lines = MAX (1, MIN (3, prompt_lines));
      }
      if (prompt_lines != MuttMessageWindow->rows)
      {
        reflow_message_window_rows (prompt_lines);
        mutt_current_menu_redraw ();
      }

      SETCOLOR (MT_COLOR_PROMPT);
      mutt_window_mvaddstr (MuttMessageWindow, 0, 0, prompt);
      NORMAL_COLOR;
      mutt_window_clrtoeol (MuttMessageWindow);
    }

    mutt_refresh ();
    /* SigWinch is not processed unless timeout is set */
    timeout (30 * 1000);
    ch  = mutt_getch ();
    timeout (-1);
    if (ch.ch == -2)
      continue;
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
  if (MuttMessageWindow->rows != 1)
  {
    reflow_message_window_rows (1);
    mutt_current_menu_redraw ();
  }
  else
    mutt_window_clearline (MuttMessageWindow, 0);
  mutt_refresh ();
  return choice;
}