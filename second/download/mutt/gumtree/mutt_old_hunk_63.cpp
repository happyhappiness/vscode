      if (!msg->env)
	msg->env = mutt_new_envelope ();

      for (i = optind; i < argc; i++)
      {
	if (url_check_scheme (argv[i]) == U_MAILTO)
	  url_parse_mailto (msg->env, &bodytext, argv[i]);
	else
	  msg->env->to = rfc822_parse_adrlist (msg->env->to, argv[i]);
      }

      if (option (OPTAUTOEDIT) && !msg->env->to && !msg->env->cc)
      {
