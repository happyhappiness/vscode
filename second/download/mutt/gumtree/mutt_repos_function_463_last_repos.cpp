int mutt_yesorno (const char *msg, int def)
{
  event_t ch;
  char *yes = _("yes");
  char *no = _("no");
  char *answer_string;
  int answer_string_wid, msg_wid;
  size_t trunc_msg_len;
  int redraw = 1, prompt_lines = 1;

#ifdef HAVE_LANGINFO_YESEXPR
  char *expr;
  regex_t reyes;
  regex_t reno;
  int reyes_ok;
  int reno_ok;
  char answer[2];

  answer[1] = 0;
  
  reyes_ok = (expr = nl_langinfo (YESEXPR)) && expr[0] == '^' &&
	     !REGCOMP (&reyes, expr, REG_NOSUB);
  reno_ok = (expr = nl_langinfo (NOEXPR)) && expr[0] == '^' &&
            !REGCOMP (&reno, expr, REG_NOSUB);
#endif

  /*
   * In order to prevent the default answer to the question to wrapped
   * around the screen in the even the question is wider than the screen,
   * ensure there is enough room for the answer and truncate the question
   * to fit.
   */
  safe_asprintf (&answer_string, " ([%s]/%s): ", def == MUTT_YES ? yes : no, def == MUTT_YES ? no : yes);
  answer_string_wid = mutt_strwidth (answer_string);
  msg_wid = mutt_strwidth (msg);

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
        prompt_lines = (msg_wid + answer_string_wid + MuttMessageWindow->cols - 1) /
          MuttMessageWindow->cols;
        prompt_lines = MAX (1, MIN (3, prompt_lines));
      }
      if (prompt_lines != MuttMessageWindow->rows)
      {
        reflow_message_window_rows (prompt_lines);
        mutt_current_menu_redraw ();
      }

      /* maxlen here is sort of arbitrary, so pick a reasonable upper bound */
      trunc_msg_len = mutt_wstr_trunc (msg, 4 * prompt_lines * MuttMessageWindow->cols,
                                       prompt_lines * MuttMessageWindow->cols - answer_string_wid,
                                       NULL);

      mutt_window_move (MuttMessageWindow, 0, 0);
      SETCOLOR (MT_COLOR_PROMPT);
      addnstr (msg, trunc_msg_len);
      addstr (answer_string);
      NORMAL_COLOR;
      mutt_window_clrtoeol (MuttMessageWindow);
    }

    mutt_refresh ();
    /* SigWinch is not processed unless timeout is set */
    timeout (30 * 1000);
    ch = mutt_getch ();
    timeout (-1);
    if (ch.ch == -2)
      continue;
    if (CI_is_return (ch.ch))
      break;
    if (ch.ch < 0)
    {
      def = -1;
      break;
    }

#ifdef HAVE_LANGINFO_YESEXPR
    answer[0] = ch.ch;
    if (reyes_ok ? 
	(regexec (& reyes, answer, 0, 0, 0) == 0) :
#else
    if (
#endif
	(tolower (ch.ch) == 'y'))
    {
      def = MUTT_YES;
      break;
    }
    else if (
#ifdef HAVE_LANGINFO_YESEXPR
	     reno_ok ?
	     (regexec (& reno, answer, 0, 0, 0) == 0) :
#endif
	     (tolower (ch.ch) == 'n'))
    {
      def = MUTT_NO;
      break;
    }
    else
    {
      BEEP();
    }
  }

  FREE (&answer_string);

#ifdef HAVE_LANGINFO_YESEXPR    
  if (reyes_ok)
    regfree (& reyes);
  if (reno_ok)
    regfree (& reno);
#endif

  if (MuttMessageWindow->rows != 1)
  {
    reflow_message_window_rows (1);
    mutt_current_menu_redraw ();
  }
  else
    mutt_window_clearline (MuttMessageWindow, 0);

  if (def != -1)
  {
    addstr ((char *) (def == MUTT_YES ? yes : no));
    mutt_refresh ();
  }
  else
  {
    /* when the users cancels with ^G, clear the message stored with
     * mutt_message() so it isn't displayed when the screen is refreshed. */
    mutt_clear_error();
  }
  return (def);
}