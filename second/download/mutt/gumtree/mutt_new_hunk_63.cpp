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

      if (option (OPTAUTOEDIT) && !msg->env->to && !msg->env->cc)
      {
