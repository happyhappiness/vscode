    
    if (!option (OPTNOCURSES))
      mutt_flushinp ();

    if (!msg)
      msg = mutt_new_header ();
    if (!msg->env)
      msg->env = mutt_new_envelope ();

    for (i = optind; i < argc; i++)
    {
      if (url_check_scheme (argv[i]) == U_MAILTO)
      {
        if (url_parse_mailto (msg->env, &bodytext, argv[i]) < 0)
	{
          if (!option (OPTNOCURSES))
            mutt_endwin (NULL);
          fputs (_("Failed to parse mailto: link\n"), stderr);
          exit (1);
	}
      }
      else
        msg->env->to = rfc822_parse_adrlist (msg->env->to, argv[i]);
    }

    if (!draftFile && option (OPTAUTOEDIT) && !msg->env->to && !msg->env->cc)
    {
      if (!option (OPTNOCURSES))
        mutt_endwin (NULL);
      fputs (_("No recipients specified.\n"), stderr);
      exit (1);
    }

    if (subject)
      msg->env->subject = safe_strdup (subject);

    if (draftFile)
      infile = draftFile;
    else if (includeFile)
      infile = includeFile;

    if (infile || bodytext)
    {
      if (infile)
      {
	if (mutt_strcmp ("-", infile) == 0)
