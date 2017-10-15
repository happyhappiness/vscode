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
	  fin = stdin;
	else 
	{
	  char path[_POSIX_PATH_MAX];
	  
	  strfcpy (path, infile, sizeof (path));
	  mutt_expand_path (path, sizeof (path));
	  if ((fin = fopen (path, "r")) == NULL)
	  {
	    if (!option (OPTNOCURSES))
	      mutt_endwin (NULL);
	    perror (path);
	    exit (1);
	  }
	}

        if (draftFile)
        {
          ENVELOPE *opts_env = msg->env;
          msg->env = mutt_read_rfc822_header (fin, NULL, 1, 0);

          rfc822_append (&msg->env->to, opts_env->to, 0);
          rfc822_append (&msg->env->cc, opts_env->cc, 0);
          rfc822_append (&msg->env->bcc, opts_env->bcc, 0);
          if (opts_env->subject)
            mutt_str_replace (&msg->env->subject, opts_env->subject);

          mutt_free_envelope (&opts_env);
        }
      }

      mutt_mktemp (buf, sizeof (buf));
      tempfile = safe_strdup (buf);

      /* is the following if still needed? */
      
      if (tempfile)
      {
	FILE *fout;

	if ((fout = safe_fopen (tempfile, "w")) == NULL)
	{
	  if (!option (OPTNOCURSES))
	    mutt_endwin (NULL);
	  perror (tempfile);
	  safe_fclose (&fin);
	  FREE (&tempfile);
	  exit (1);
	}
	if (fin)
	  mutt_copy_stream (fin, fout);
	else if (bodytext)
	  fputs (bodytext, fout);
	safe_fclose (&fout);
      }

      if (fin && fin != stdin)
        safe_fclose (&fin);
    }

    FREE (&bodytext);
    
    if (attach)
    {
      LIST *t = attach;
      BODY *a = NULL;

      while (t)
      {
	if (a)
	{
	  a->next = mutt_make_file_attach (t->data);
