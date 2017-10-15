    }

    if (subject)
      msg->env->subject = safe_strdup (subject);

    if (draftFile)
    {
      infile = draftFile;
      includeFile = NULL;
    }
    else if (includeFile)
      infile = includeFile;
    else
      edit_infile = 0;

    if (infile || bodytext)
    {
      /* Prepare fin and expanded_infile. */
      if (infile)
      {
	if (mutt_strcmp ("-", infile) == 0)
        {
          if (edit_infile)
          {
            fputs (_("Cannot use -E flag with stdin\n"), stderr);
            exit (1);
          }
	  fin = stdin;
        }
	else
	{
	  strfcpy (expanded_infile, infile, sizeof (expanded_infile));
	  mutt_expand_path (expanded_infile, sizeof (expanded_infile));
	  if ((fin = fopen (expanded_infile, "r")) == NULL)
	  {
	    if (!option (OPTNOCURSES))
	      mutt_endwin (NULL);
	    perror (expanded_infile);
	    exit (1);
	  }
	}
      }

      /* Copy input to a tempfile, and re-point fin to the tempfile.
       * Note: stdin is always copied to a tempfile, ensuring draftFile
       * can stat and get the correct st_size below.
       */
      if (!edit_infile)
      {
        mutt_mktemp (buf, sizeof (buf));
        tempfile = safe_strdup (buf);

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
        {
	  mutt_copy_stream (fin, fout);
          if (fin != stdin)
            safe_fclose (&fin);
        }
	else if (bodytext)
	  fputs (bodytext, fout);
	safe_fclose (&fout);

        if ((fin = fopen (tempfile, "r")) == NULL)
        {
          if (!option (OPTNOCURSES))
            mutt_endwin (NULL);
          perror (tempfile);
          FREE (&tempfile);
          exit (1);
        }
      }
      /* If editing the infile, keep it around afterwards so
       * it doesn't get unlinked, and we can rebuild the draftFile
       */
      else
        sendflags |= SENDNOFREEHEADER;

      /* Parse the draftFile into the full HEADER/BODY structure.
       * Set SENDDRAFTFILE so ci_send_message doesn't overwrite
       * our msg->content.
       */
      if (draftFile)
      {
        HEADER *context_hdr = NULL;
        ENVELOPE *opts_env = msg->env;
        struct stat st;
        LIST *uh, **last_uhp;

        sendflags |= SENDDRAFTFILE;

        /* Set up a "context" header with just enough information so that
         * mutt_prepare_template() can parse the message in fin.
         */
        context_hdr = mutt_new_header ();
        context_hdr->offset = 0;
        context_hdr->content = mutt_new_body ();
        if (fstat (fileno (fin), &st))
        {
          perror (draftFile);
          exit (1);
        }
        context_hdr->content->length = st.st_size;

        mutt_prepare_template (fin, NULL, msg, context_hdr, 0);

        /* Scan for mutt header to set OPTRESUMEDRAFTFILES */
        for (last_uhp = &msg->env->userhdrs, uh = *last_uhp;
             uh; uh = *last_uhp)
        {
          if (ascii_strncasecmp ("X-Mutt-Resume-Draft:", uh->data, 20) == 0)
          {
            if (option (OPTRESUMEEDITEDDRAFTFILES))
              set_option (OPTRESUMEDRAFTFILES);

            *last_uhp = uh->next;
            uh->next = NULL;
            mutt_free_list (&uh);
          }
          else
            last_uhp = &uh->next;
        }

        rfc822_append (&msg->env->to, opts_env->to, 0);
        rfc822_append (&msg->env->cc, opts_env->cc, 0);
        rfc822_append (&msg->env->bcc, opts_env->bcc, 0);
        if (opts_env->subject)
          mutt_str_replace (&msg->env->subject, opts_env->subject);

        mutt_free_envelope (&opts_env);
        mutt_free_header (&context_hdr);
      }
      /* Editing the includeFile: pass it directly in.
       * Note that SENDNOFREEHEADER is set above so it isn't unlinked.
       */
      else if (edit_infile)
        bodyfile = expanded_infile;
      /* For bodytext and unedited includeFile: use the tempfile.
       */
      else
        bodyfile = tempfile;

      if (fin)
        safe_fclose (&fin);
    }

    FREE (&bodytext);

    if (attach)
    {
      LIST *t = attach;
      BODY *a = msg->content;

      while (a && a->next)
        a = a->next;

      while (t)
      {
	if (a)
	{
	  a->next = mutt_make_file_attach (t->data);
