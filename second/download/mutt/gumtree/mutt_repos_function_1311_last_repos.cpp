int
mutt_invoke_sendmail (ADDRESS *from,	/* the sender */
		 ADDRESS *to, ADDRESS *cc, ADDRESS *bcc, /* recips */
		 const char *msg, /* file containing message */
		 int eightbit) /* message contains 8bit chars */
{
  char *ps = NULL, *path = NULL, *s = safe_strdup (Sendmail), *childout = NULL;
  char **args = NULL;
  size_t argslen = 0, argsmax = 0;
  char **extra_args = NULL;
  size_t extra_argslen = 0, extra_argsmax = 0;
  int i;

  /* ensure that $sendmail is set to avoid a crash. http://dev.mutt.org/trac/ticket/3548 */
  if (!s)
  {
    mutt_error(_("$sendmail must be set in order to send mail."));
    return -1;
  }

  ps = s;
  i = 0;
  while ((ps = strtok (ps, " ")))
  {
    if (argslen == argsmax)
      safe_realloc (&args, sizeof (char *) * (argsmax += 5));

    if (i)
    {
      if (!mutt_strcmp (ps, "--"))
        break;
      args[argslen++] = ps;
    }
    else
    {
      path = safe_strdup (ps);
      ps = strrchr (ps, '/');
      if (ps)
	ps++;
      else
	ps = path;
      args[argslen++] = ps;
    }
    ps = NULL;
    i++;
  }

  /* If Sendmail contained a "--", we save the recipients to append to
   * args after other possible options added below. */
  if (ps)
  {
    ps = NULL;
    while ((ps = strtok (ps, " ")))
    {
      if (extra_argslen == extra_argsmax)
        safe_realloc (&extra_args, sizeof (char *) * (extra_argsmax += 5));

      extra_args[extra_argslen++] = ps;
      ps = NULL;
    }
  }

  if (eightbit && option (OPTUSE8BITMIME))
    args = add_option (args, &argslen, &argsmax, "-B8BITMIME");

  if (option (OPTENVFROM))
  {
    if (EnvFrom)
    {
      args = add_option (args, &argslen, &argsmax, "-f");
      args = add_args   (args, &argslen, &argsmax, EnvFrom);
    }
    else if (from && !from->next)
    {
      args = add_option (args, &argslen, &argsmax, "-f");
      args = add_args   (args, &argslen, &argsmax, from);
    }
  }

  if (DsnNotify)
  {
    args = add_option (args, &argslen, &argsmax, "-N");
    args = add_option (args, &argslen, &argsmax, DsnNotify);
  }
  if (DsnReturn)
  {
    args = add_option (args, &argslen, &argsmax, "-R");
    args = add_option (args, &argslen, &argsmax, DsnReturn);
  }
  args = add_option (args, &argslen, &argsmax, "--");
  for (i = 0; i < extra_argslen; i++)
    args = add_option (args, &argslen, &argsmax, extra_args[i]);
  args = add_args (args, &argslen, &argsmax, to);
  args = add_args (args, &argslen, &argsmax, cc);
  args = add_args (args, &argslen, &argsmax, bcc);

  if (argslen == argsmax)
    safe_realloc (&args, sizeof (char *) * (++argsmax));

  args[argslen++] = NULL;

  /* Some user's $sendmail command uses gpg for password decryption,
   * and is set up to prompt using ncurses pinentry.  If we
   * mutt_endwin() it leaves other users staring at a blank screen.
   * So instead, just force a hard redraw on the next refresh. */
  if (!option (OPTNOCURSES))
    mutt_need_hard_redraw ();

  if ((i = send_msg (path, args, msg, option(OPTNOCURSES) ? NULL : &childout)) != (EX_OK & 0xff))
  {
    if (i != S_BKG)
    {
      const char *e;

      e = mutt_strsysexit (i);
      mutt_error (_("Error sending message, child exited %d (%s)."), i, NONULL (e));
      if (childout)
      {
	struct stat st;

	if (stat (childout, &st) == 0 && st.st_size > 0)
	  mutt_do_pager (_("Output of the delivery process"), childout, 0, NULL);
      }
    }
  }
  else if (childout)
    unlink (childout);

  FREE (&childout);
  FREE (&path);
  FREE (&s);
  FREE (&args);
  FREE (&extra_args);

  if (i == (EX_OK & 0xff))
    i = 0;
  else if (i == S_BKG)
    i = 1;
  else
    i = -1;
  return (i);
}