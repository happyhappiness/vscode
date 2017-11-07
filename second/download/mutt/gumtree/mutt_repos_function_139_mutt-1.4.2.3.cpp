static int _mutt_pipe_message (HEADER *h, char *cmd,
			       int decode,
			       int print,
			       int split,
			       char *sep)
{
  
  int i, rc = 0;
  pid_t thepid;
  FILE *fpout;
  
  mutt_endwin (NULL);
  if (h)
  {

    mutt_message_hook (Context, h, M_MESSAGEHOOK);

#ifdef HAVE_PGP
    if (decode)
    {
      mutt_parse_mime_message (Context, h);
      if(h->pgp & PGPENCRYPT && !pgp_valid_passphrase())
	return 1;
    }
    mutt_endwin (NULL);
#endif

    if ((thepid = mutt_create_filter (cmd, &fpout, NULL, NULL)) < 0)
    {
      mutt_perror _("Can't create filter process");
      return 1;
    }
      
    pipe_msg (h, fpout, decode, print);
    safe_fclose (&fpout);
    rc = mutt_wait_filter (thepid);
  }
  else
  { /* handle tagged messages */



#ifdef HAVE_PGP

    if (decode)
    {
      for (i = 0; i < Context->vcount; i++)
	if(Context->hdrs[Context->v2r[i]]->tagged)
	{
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], M_MESSAGEHOOK);
	  mutt_parse_mime_message(Context, Context->hdrs[Context->v2r[i]]);
	  if (Context->hdrs[Context->v2r[i]]->pgp & PGPENCRYPT &&
	      !pgp_valid_passphrase())
	    return 1;
	}
    }
#endif
    
    if (split)
    {
      for (i = 0; i < Context->vcount; i++)
      {
        if (Context->hdrs[Context->v2r[i]]->tagged)
        {
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], M_MESSAGEHOOK);
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
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], M_MESSAGEHOOK);
          pipe_msg (Context->hdrs[Context->v2r[i]], fpout, decode, print);
          /* add the message separator */
          if (sep) fputs (sep, fpout);
        }
      }
      safe_fclose (&fpout);
      if (mutt_wait_filter (thepid) != 0)
	rc = 1;
    }
  }

  if (rc || option (OPTWAITKEY))
    mutt_any_key_to_continue (NULL);
  return rc;
}