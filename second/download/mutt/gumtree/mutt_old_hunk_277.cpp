	  mutt_endwin (NULL);
	  if ((thepid = mutt_create_filter (cmd, &fpout, NULL, NULL)) < 0)
	  {
	    mutt_perror _("Can't create filter process");
	    return 1;
	  }
          pipe_msg (Context->hdrs[Context->v2r[i]], fpout, decode, print);
          /* add the message separator */
          if (sep)  fputs (sep, fpout);
	  safe_fclose (&fpout);
	  if (mutt_wait_filter (thepid) != 0)
	    rc = 1;
        }
      }
    }
    else
    {
      mutt_endwin (NULL);
      if ((thepid = mutt_create_filter (cmd, &fpout, NULL, NULL)) < 0)
      {
	mutt_perror _("Can't create filter process");
	return 1;
      }
      for (i = 0; i < Context->vcount; i++)
      {
        if (Context->hdrs[Context->v2r[i]]->tagged)
        {
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], MUTT_MESSAGEHOOK);
          pipe_msg (Context->hdrs[Context->v2r[i]], fpout, decode, print);
