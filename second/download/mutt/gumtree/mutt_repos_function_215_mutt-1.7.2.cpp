int mutt_display_message (HEADER *cur)
{
  char tempfile[_POSIX_PATH_MAX], buf[LONG_STRING];
  int rc = 0, builtin = 0;
  int cmflags = MUTT_CM_DECODE | MUTT_CM_DISPLAY | MUTT_CM_CHARCONV;
  FILE *fpout = NULL;
  FILE *fpfilterout = NULL;
  pid_t filterpid = -1;
  int res;

  snprintf (buf, sizeof (buf), "%s/%s", TYPE (cur->content),
	    cur->content->subtype);

  mutt_parse_mime_message (Context, cur);
  mutt_message_hook (Context, cur, MUTT_MESSAGEHOOK);

  /* see if crypto is needed for this message.  if so, we should exit curses */
  if (WithCrypto && cur->security)
  {
    if (cur->security & ENCRYPT)
    {
      if (cur->security & APPLICATION_SMIME)
	crypt_smime_getkeys (cur->env);
      if(!crypt_valid_passphrase(cur->security))
	return 0;

      cmflags |= MUTT_CM_VERIFY;
    }
    else if (cur->security & SIGN)
    {
      /* find out whether or not the verify signature */
      if (query_quadoption (OPT_VERIFYSIG, _("Verify PGP signature?")) == MUTT_YES)
      {
	cmflags |= MUTT_CM_VERIFY;
      }
    }
  }
  
  if (cmflags & MUTT_CM_VERIFY || cur->security & ENCRYPT)
  {
    if (cur->security & APPLICATION_PGP)
    {
      if (cur->env->from)
        crypt_pgp_invoke_getkeys (cur->env->from);
      
      crypt_invoke_message (APPLICATION_PGP);
    }

    if (cur->security & APPLICATION_SMIME)
      crypt_invoke_message (APPLICATION_SMIME);
  }


  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((fpout = safe_fopen (tempfile, "w")) == NULL)
  {
    mutt_error _("Could not create temporary file!");
    return (0);
  }

  if (DisplayFilter && *DisplayFilter) 
  {
    fpfilterout = fpout;
    fpout = NULL;
    /* mutt_endwin (NULL); */
    filterpid = mutt_create_filter_fd (DisplayFilter, &fpout, NULL, NULL,
				       -1, fileno(fpfilterout), -1);
    if (filterpid < 0)
    {
      mutt_error (_("Cannot create display filter"));
      safe_fclose (&fpfilterout);
      unlink (tempfile);
      return 0;
    }
  }

  if (!Pager || mutt_strcmp (Pager, "builtin") == 0)
    builtin = 1;
  else
  {
    struct hdr_format_info hfi;
    hfi.ctx = Context;
    hfi.pager_progress = ExtPagerProgress;
    hfi.hdr = cur;
    mutt_make_string_info (buf, sizeof (buf), MuttIndexWindow->cols, NONULL(PagerFmt), &hfi, MUTT_FORMAT_MAKEPRINT);
    fputs (buf, fpout);
    fputs ("\n\n", fpout);
  }

  res = mutt_copy_message (fpout, Context, cur, cmflags,
       	(option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) | CH_DECODE | CH_FROM | CH_DISPLAY);
  if ((safe_fclose (&fpout) != 0 && errno != EPIPE) || res < 0)
  {
    mutt_error (_("Could not copy message"));
    if (fpfilterout != NULL)
    {
      mutt_wait_filter (filterpid);
      safe_fclose (&fpfilterout);
    }
    mutt_unlink (tempfile);
    return 0;
  }

  if (fpfilterout != NULL && mutt_wait_filter (filterpid) != 0)
    mutt_any_key_to_continue (NULL);

  safe_fclose (&fpfilterout);	/* XXX - check result? */

  
  if (WithCrypto)
  {
    /* update crypto information for this message */
    cur->security &= ~(GOODSIGN|BADSIGN);
    cur->security |= crypt_query (cur->content);
  
    /* Remove color cache for this message, in case there
       are color patterns for both ~g and ~V */
    cur->pair = 0;
  }

  if (builtin)
  {
    pager_t info;

    if (WithCrypto 
        && (cur->security & APPLICATION_SMIME) && (cmflags & MUTT_CM_VERIFY))
    {
      if (cur->security & GOODSIGN)
      {
	if (!crypt_smime_verify_sender(cur))
	  mutt_message ( _("S/MIME signature successfully verified."));
	else
	  mutt_error ( _("S/MIME certificate owner does not match sender."));
      }
      else if (cur->security & PARTSIGN)
	mutt_message (_("Warning: Part of this message has not been signed."));
      else if (cur->security & SIGN || cur->security & BADSIGN)
	mutt_error ( _("S/MIME signature could NOT be verified."));
    }

    if (WithCrypto 
        && (cur->security & APPLICATION_PGP) && (cmflags & MUTT_CM_VERIFY))
    {
      if (cur->security & GOODSIGN)
	mutt_message (_("PGP signature successfully verified."));
      else if (cur->security & PARTSIGN)
	mutt_message (_("Warning: Part of this message has not been signed."));
      else if (cur->security & SIGN)
	mutt_message (_("PGP signature could NOT be verified."));
    }

    /* Invoke the builtin pager */
    memset (&info, 0, sizeof (pager_t));
    info.hdr = cur;
    info.ctx = Context;
    rc = mutt_pager (NULL, tempfile, MUTT_PAGER_MESSAGE, &info);
  }
  else
  {
    int r;

    mutt_endwin (NULL);
    snprintf (buf, sizeof (buf), "%s %s", NONULL(Pager), tempfile);
    if ((r = mutt_system (buf)) == -1)
      mutt_error (_("Error running \"%s\"!"), buf);
    unlink (tempfile);
    if (!option (OPTNOCURSES))
      keypad (stdscr, TRUE);
    if (r != -1)
      mutt_set_flag (Context, cur, MUTT_READ, 1);
    if (r != -1 && option (OPTPROMPTAFTER))
    {
      mutt_unget_event (mutt_any_key_to_continue _("Command: "), 0);
      rc = km_dokey (MENU_PAGER);
    }
    else
      rc = 0;
  }

  return rc;
}