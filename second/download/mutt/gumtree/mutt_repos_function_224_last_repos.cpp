static int _mutt_pipe_message (HEADER *h, char *cmd,
			       int decode,
			       int print,
			       int split,
			       char *sep)
{
  
  int i, rc = 0;
  pid_t thepid;
  FILE *fpout;
  
/*   mutt_endwin (NULL); 

     is this really needed here ? 
     it makes the screen flicker on pgp and s/mime messages,
     before asking for a passphrase...
                                     Oliver Ehli */
  if (h)
  {

    mutt_message_hook (Context, h, MUTT_MESSAGEHOOK);

    if (WithCrypto && decode)
    {
      mutt_parse_mime_message (Context, h);
      if(h->security & ENCRYPT && !crypt_valid_passphrase(h->security))
	return 1;
    }
    mutt_endwin (NULL);

    if ((thepid = mutt_create_filter (cmd, &fpout, NULL, NULL)) < 0)
    {
      mutt_perror _("Can't create filter process");
      return 1;
    }

    set_option (OPTKEEPQUIET);
    pipe_msg (h, fpout, decode, print);
    safe_fclose (&fpout);
    rc = mutt_wait_filter (thepid);
    unset_option (OPTKEEPQUIET);
  }
  else
  { /* handle tagged messages */

    if (WithCrypto && decode)
    {
      for (i = 0; i < Context->vcount; i++)
	if(Context->hdrs[Context->v2r[i]]->tagged)
	{
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], MUTT_MESSAGEHOOK);
	  mutt_parse_mime_message(Context, Context->hdrs[Context->v2r[i]]);
	  if (Context->hdrs[Context->v2r[i]]->security & ENCRYPT &&
	      !crypt_valid_passphrase(Context->hdrs[Context->v2r[i]]->security))
	    return 1;
	}
    }
    
    if (split)
    {
      for (i = 0; i < Context->vcount; i++)
      {
        if (Context->hdrs[Context->v2r[i]]->tagged)
        {
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], MUTT_MESSAGEHOOK);
	  mutt_endwin (NULL);
	  if ((thepid = mutt_create_filter (cmd, &fpout, NULL, NULL)) < 0)
	  {
	    mutt_perror _("Can't create filter process");
	    return 1;
	  }
          set_option (OPTKEEPQUIET);
          pipe_msg (Context->hdrs[Context->v2r[i]], fpout, decode, print);
          /* add the message separator */
          if (sep)  fputs (sep, fpout);
	  safe_fclose (&fpout);
	  if (mutt_wait_filter (thepid) != 0)
	    rc = 1;
          unset_option (OPTKEEPQUIET);
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
      set_option (OPTKEEPQUIET);
      for (i = 0; i < Context->vcount; i++)
      {
        if (Context->hdrs[Context->v2r[i]]->tagged)
        {
	  mutt_message_hook (Context, Context->hdrs[Context->v2r[i]], MUTT_MESSAGEHOOK);
          pipe_msg (Context->hdrs[Context->v2r[i]], fpout, decode, print);
          /* add the message separator */
          if (sep) fputs (sep, fpout);
        }
      }
      safe_fclose (&fpout);
      if (mutt_wait_filter (thepid) != 0)
	rc = 1;
      unset_option (OPTKEEPQUIET);
    }
  }

  if (rc || option (OPTWAITKEY))
    mutt_any_key_to_continue (NULL);
  return rc;
}