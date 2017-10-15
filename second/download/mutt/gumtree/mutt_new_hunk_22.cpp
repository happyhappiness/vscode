void mutt_edit_file (const char *editor, const char *data)
{
  char cmd[LONG_STRING];
  
  mutt_endwin (NULL);
  mutt_expand_file_fmt (cmd, sizeof (cmd), editor, data);
  if (mutt_system (cmd))
  {
    mutt_error (_("Error running \"%s\"!"), cmd);
    mutt_sleep (2);
  }
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
  /* the terminal may have been resized while the editor owned it */
  mutt_resize_screen ();
#endif
  keypad (stdscr, TRUE);
  clearok (stdscr, TRUE);
}

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

  CLEARLINE(LINES-1);

  /*
   * In order to prevent the default answer to the question to wrapped
   * around the screen in the even the question is wider than the screen,
   * ensure there is enough room for the answer and truncate the question
   * to fit.
   */
  safe_asprintf (&answer_string, " ([%s]/%s): ", def == M_YES ? yes : no, def == M_YES ? no : yes);
  answer_string_len = mutt_strwidth (answer_string);
  /* maxlen here is sort of arbitrary, so pick a reasonable upper bound */
  msglen = mutt_wstr_trunc (msg, 4*COLS, COLS - answer_string_len, NULL);
  addnstr (msg, msglen);
  addstr (answer_string);
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
