int mutt_yesorno (const char *msg, int def)
{
  event_t ch;
  char *yes = _("yes");
  char *no = _("no");
  char *answer_string;
  size_t answer_string_len;
  size_t msglen;

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

  mutt_window_clearline (MuttMessageWindow, 0);

  /*
   * In order to prevent the default answer to the question to wrapped
   * around the screen in the even the question is wider than the screen,
   * ensure there is enough room for the answer and truncate the question
   * to fit.
   */
  safe_asprintf (&answer_string, " ([%s]/%s): ", def == MUTT_YES ? yes : no, def == MUTT_YES ? no : yes);
  answer_string_len = mutt_strwidth (answer_string);
  /* maxlen here is sort of arbitrary, so pick a reasonable upper bound */
  msglen = mutt_wstr_trunc (msg, 4*MuttMessageWindow->cols, MuttMessageWindow->cols - answer_string_len, NULL);
  SETCOLOR (MT_COLOR_PROMPT);
  addnstr (msg, msglen);
  addstr (answer_string);
  NORMAL_COLOR;
  FREE (&answer_string);

  FOREVER
  {
    mutt_refresh ();
    ch = mutt_getch ();
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

#ifdef HAVE_LANGINFO_YESEXPR    
  if (reyes_ok)
    regfree (& reyes);
  if (reno_ok)
    regfree (& reno);
#endif

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