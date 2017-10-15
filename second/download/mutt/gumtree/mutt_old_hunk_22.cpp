void mutt_edit_file (const char *editor, const char *data)
{
  char cmd[LONG_STRING];
  
  mutt_endwin (NULL);
  mutt_expand_file_fmt (cmd, sizeof (cmd), editor, data);
  if (mutt_system (cmd) == -1)
    mutt_error (_("Error running \"%s\"!"), cmd);
  keypad (stdscr, TRUE);
  clearok (stdscr, TRUE);
}

int mutt_yesorno (const char *msg, int def)
{
  event_t ch;
  char *yes = _("yes");
  char *no = _("no");

#ifdef HAVE_LANGINFO_YESEXPR
  char *expr;
  regex_t reyes;
  regex_t reno;
  int reyes_ok;
  int reno_ok;
  char answer[2];

  answer[1] = 0;
  
  reyes_ok = (expr = nl_langinfo (YESEXPR)) && expr[0] == '^' &&
	     !regcomp (&reyes, expr, REG_NOSUB|REG_EXTENDED);
  reno_ok = (expr = nl_langinfo (NOEXPR)) && expr[0] == '^' &&
            !regcomp (&reno, expr, REG_NOSUB|REG_EXTENDED);
#endif

  CLEARLINE(LINES-1);
  printw ("%s ([%s]/%s): ", msg, def ? yes : no, def ? no : yes);
  FOREVER
  {
    mutt_refresh ();
    ch = mutt_getch ();
    if (CI_is_return (ch.ch))
      break;
    if (ch.ch == -1)
    {
      def = -1;
      break;
    }

#ifdef HAVE_LANGINFO_YESEXPR
